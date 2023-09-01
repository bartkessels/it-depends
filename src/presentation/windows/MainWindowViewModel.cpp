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

MainWindowViewModel::~MainWindowViewModel()
{
	loadingThread.detach();
}

void MainWindowViewModel::loadSBOM(domain::SbomType type, const std::string& fileLocation)
{
	// Set state to loading
	window->updateState(std::make_shared<states::LoadingState>());

	// Execute background task
	loadingThread = std::thread([this, type, fileLocation]() {
		try {
			const auto& mapper = mapperFactory->getMapper(type);
			const auto& dependencies = mapper->map(fileLocation);

			window->updateState(std::make_shared<states::SuccessState>(dependencies));
		} catch (std::exception& e) {
			window->updateState(std::make_shared<states::ErrorState>(e.what()));
		}
	});
}
