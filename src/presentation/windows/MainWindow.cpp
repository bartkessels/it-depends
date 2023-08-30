#include "presentation/windows/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace id::presentation::windows;
using namespace id::presentation;

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow())
{
	ui->setupUi(this);

	connect(this, &MainWindow::changeState, this, &MainWindow::handleStateChange);
	connect(ui->actionOpenCycloneDX, &QAction::triggered, this, &MainWindow::openCycloneDXFile);
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
	if (const auto& result = std::dynamic_pointer_cast<states::SuccessState>(state))
	{
		// Display dependencies
	}
	else if (const auto& error = std::dynamic_pointer_cast<states::ErrorState>(state))
	{
		QMessageBox::critical(this, "An error occurred", QString::fromStdString(error->message), QMessageBox::Ok, QMessageBox::NoButton);
	}
	else if (std::dynamic_pointer_cast<states::LoadingState>(state))
	{
		// Handle loading state
	}
	else if (std::dynamic_pointer_cast<states::EmptyState>(state))
	{
		// Handle empty state
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