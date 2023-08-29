#include "presentation/windows/MainWindowViewModel.hpp"

using namespace id::presentation::windows;

MainWindowViewModel::MainWindowViewModel(
	const std::shared_ptr<IMainWindow>& window,
	std::shared_ptr<id::data::contracts::IMapperFactory> mapperFactory
):
	window(window),
	mapperFactory(std::move(mapperFactory))
{
	window->updateState(std::make_shared<states::EmptyState>());
}

void MainWindowViewModel::loadSBOM(domain::SbomType type, const std::string& fileLocation)
{
	// Set state to loading
	window->updateState(std::make_shared<states::LoadingState>());

	// Execute background task
	std::async(std::launch::async, [this, type, fileLocation]() {
		try {
			const auto& mapper = this->mapperFactory->getMapper(type);
			const auto& dependencies = mapper->map(fileLocation);
			const auto& state = std::make_shared<states::SuccessState>(dependencies);

			window->updateState(state);
		} catch (std::exception& e) {
			const auto& state = std::make_shared<states::ErrorState>(e.what());
			window->updateState(state);
		}

	}).get();

	// Update state accordingly
}