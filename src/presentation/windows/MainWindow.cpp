#include "presentation/windows/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace id::presentation::windows;
using namespace id::presentation;

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow())
{
	ui->setupUi(this);
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
	if (const auto& result = std::dynamic_pointer_cast<states::SuccessState>(state))
	{
		// Display dependencies
	}
	else if (const auto& error = std::dynamic_pointer_cast<states::ErrorState>(state))
	{
		// Handle error
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
