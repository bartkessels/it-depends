#include "presentation/windows/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace id::presentation::windows;
using namespace id::presentation;

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow())
{
	ui->setupUi(this);
	ui->dependencies->viewport()->setStyleSheet("background-color: transparent;");
	ui->description->viewport()->setStyleSheet("background-color: transparent;");
	ui->urls->viewport()->setStyleSheet("background-color: transparent;");

	connect(this, &MainWindow::changeState, this, &MainWindow::handleStateChange);
	connect(ui->actionOpenCycloneDX, &QAction::triggered, this, &MainWindow::openCycloneDXFile);
	connect(ui->dependencies, &QListWidget::itemPressed, this, &MainWindow::displayDependencyDetails);
	connect(ui->urls, &QListWidget::itemDoubleClicked, this, &MainWindow::openUrl);
	connect(ui->filter, &QLineEdit::textChanged, this, &MainWindow::filterList);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setViewModel(const std::shared_ptr<IMainWindowViewModel>& viewModel)
{
	this->viewModel = viewModel;
}

void MainWindow::updateState(const std::shared_ptr<states::MainWindowState>& state)
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
	const auto& data = item->data(Qt::UserRole);
	const auto& dependency = qvariant_cast<std::shared_ptr<models::DependencyUiModel>>(data);
	displayDependency(dependency);
}

void MainWindow::openUrl(QListWidgetItem* item)
{
	const auto& uri = item->data(Qt::UserRole).toUrl();
	QDesktopServices::openUrl(uri);
}

void MainWindow::displayDependency(const std::shared_ptr<models::DependencyUiModel>& dependency)
{
	ui->icon->setPixmap(QIcon(dependency->iconName).pixmap(ICON_SIZE, ICON_SIZE));
	ui->name->setText(dependency->name);
	ui->version->setText(dependency->version);
	ui->description->document()->setPlainText(dependency->description);
	ui->author->setText(dependency->author);

	ui->urls->clear();
	for (const auto& url: dependency->urls) {
		auto* urlWidget = new QListWidgetItem(ui->urls);
		urlWidget->setText(url->name);
		urlWidget->setData(Qt::UserRole, QVariant(url->uri));
		ui->urls->addItem(urlWidget);
	}
}

void MainWindow::loadDependenciesIntoList(const std::vector<std::shared_ptr<models::DependencyUiModel>>& dependencies, QListWidget* listWidget)
{
	listWidget->clear();

	for (const auto& dependency: dependencies) {
		auto* listWidgetItem = new QListWidgetItem(listWidget);
		auto* dependencyWidget = new widgets::DependencyListWidget(dependency, listWidget);

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

void MainWindow::filterList(const QString& searchQuery)
{
	for (int index = 0; index < ui->dependencies->count(); index++) {
		const auto& widget = ui->dependencies->item(index);
		const auto& data = widget->data(Qt::UserRole);
		const auto& dependency = qvariant_cast<std::shared_ptr<models::DependencyUiModel>>(data);

//		if (searchQuery.isEmpty() || QString::fromStdString(dependency->name).contains(searchQuery)) {
//			widget->setHidden(false);
//		} else {
//			widget->setHidden(true);
//		}



		widget->setHidden(
			!searchQuery.isEmpty() &&
			!dependency->name.contains(searchQuery)
		);
	}
}
