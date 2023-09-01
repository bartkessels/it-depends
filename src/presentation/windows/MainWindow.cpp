#include "presentation/windows/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace id::presentation::windows;
using namespace id::presentation;

MainWindow::MainWindow(
	const std::shared_ptr<contracts::IUiMapper<domain::models::Dependency, models::DependencyListItemUiModel>>& dependencyListItemUiMapper,
	const std::shared_ptr<contracts::IUiMapper<domain::models::Url, models::UrlUiModel>>& urlUiMapper,
	QWidget* parent
):
		QMainWindow(parent),
		dependencyListItemUiMapper(dependencyListItemUiMapper),
		urlUiMapper(urlUiMapper),
		ui(new Ui::MainWindow())
{
	ui->setupUi(this);
	ui->dependencies->viewport()->setStyleSheet("background-color: transparent;");
	ui->description->viewport()->setStyleSheet("background-color: transparent;");
	ui->urls->viewport()->setStyleSheet("background-color: transparent;");
	ui->transitiveDependencies->viewport()->setStyleSheet("background-color: transparent;");

	connect(this, &MainWindow::changeState, this, &MainWindow::handleStateChange);
	connect(ui->actionOpenCycloneDX, &QAction::triggered, this, &MainWindow::openCycloneDXFile);
	connect(ui->dependencies, &QListWidget::itemClicked, this, &MainWindow::displayDependencyDetails);
	connect(ui->urls, &QListWidget::itemPressed, this, &MainWindow::openUrl);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setViewModel(std::shared_ptr<IMainWindowViewModel> viewModel)
{
	this->viewModel = viewModel;
}

void MainWindow::updateState(std::shared_ptr<states::MainWindowState> state)
{
	if (state != nullptr) {
		emit changeState(state);
	}
}

void MainWindow::handleStateChange(std::shared_ptr<states::MainWindowState> state)
{
	QApplication::restoreOverrideCursor();
	ui->loading->hide();
	ui->success->hide();

	if (const auto& result = std::dynamic_pointer_cast<states::SuccessState>(state))
	{
		ui->success->show();

		if (!result->dependencies.empty()) {
			loadDependenciesIntoList(result->dependencies, ui->dependencies);
		}
	}
	else if (const auto& error = std::dynamic_pointer_cast<states::ErrorState>(state))
	{
		QMessageBox::critical(this, "An error occurred", QString::fromStdString(error->message), QMessageBox::Ok, QMessageBox::NoButton);
	}
	else if (std::dynamic_pointer_cast<states::LoadingState>(state))
	{
		ui->success->hide();
		QApplication::setOverrideCursor(Qt::WaitCursor);
		ui->loading->show();
	}
	else if (std::dynamic_pointer_cast<states::EmptyState>(state))
	{
		// Handle empty state
	}
}

void MainWindow::displayDependencyDetails(QListWidgetItem* item)
{
	ui->dependencies->setCurrentItem(item);
	item->setSelected(true);

	const auto& data = item->data(Qt::UserRole);
	const auto& dependency = qvariant_cast<std::shared_ptr<domain::models::Dependency>>(data);
	displayDependency(dependency);
}

void MainWindow::openUrl(QListWidgetItem* item)
{
	const auto& uri = item->data(Qt::UserRole).toUrl();
	QDesktopServices::openUrl(uri);
}

void MainWindow::displayDependency(std::shared_ptr<domain::models::Dependency> dependency)
{
	ui->name->setText(QString::fromStdString(dependency->name));
	ui->version->setText(QString::fromStdString(dependency->version));
	ui->description->document()->setPlainText(QString::fromStdString(dependency->description));

	if (dependency->author != nullptr) {
		ui->author->setText(QString::fromStdString(dependency->author->name));
	}

	ui->urls->clear();
	for (const auto& url: dependency->urls) {
		const auto& uiModel = urlUiMapper->map(url);

		auto* urlWidget = new QListWidgetItem(ui->urls);
		urlWidget->setText(uiModel->name);
		urlWidget->setData(Qt::UserRole, QVariant(uiModel->uri));
		ui->urls->addItem(urlWidget);
	}

//	loadTransitiveDependencies(dependency->dependencies);
	loadDependenciesIntoList(dependency->dependencies, ui->transitiveDependencies);
}

void MainWindow::loadDependenciesIntoList(std::vector<std::shared_ptr<domain::models::Dependency>> dependencies, QListWidget* listWidget)
{
	listWidget->clear();

	for (const auto& dependency: dependencies) {
		const auto& uiModel = dependencyListItemUiMapper->map(dependency);
		auto* listWidgetItem = new QListWidgetItem(listWidget);
		auto* dependencyWidget = new widgets::DependencyListWidget(uiModel, listWidget);

		listWidgetItem->setData(Qt::UserRole, QVariant::fromValue(dependency));
		listWidgetItem->setSizeHint(dependencyWidget->sizeHint());

		listWidget->setItemWidget(listWidgetItem, dependencyWidget);
	}
}

void MainWindow::openCycloneDXFile()
{
	const auto& filePath = openFile();
	viewModel->loadSBOM(SbomType::CycloneDX, filePath);
}

std::string MainWindow::openFile()
{
	const auto& filePath = QFileDialog::getOpenFileUrl(this, "Open SBOM", QUrl());
	return filePath.toLocalFile().toStdString();
}