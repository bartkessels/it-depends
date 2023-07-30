#include "presentation/windows/MainWindowViewModel.hpp"

using namespace id::presentation::windows;

MainWindowViewModel::MainWindowViewModel(std::shared_ptr<IMainWindow> window):
	window(window)
{
	window->updateState(std::make_shared<states::EmptyState>());
}

void MainWindowViewModel::loadSBOM(std::shared_ptr<domain::SbomType> type, std::string fileLocation)
{
	// Set state to loading
	window->updateState(std::make_shared<states::EmptyState>());

	// Execute background task

	// Update state accordingly
}