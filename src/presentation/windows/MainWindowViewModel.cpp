#include "presentation/windows/MainWindowViewModel.hpp"

using namespace id::presentation::windows;

MainWindowViewModel::MainWindowViewModel(
	const std::shared_ptr<IMainWindow>& window,
	const std::shared_ptr<data::contracts::IMapperFactory>& mapperFactory,
	const std::shared_ptr<contracts::IUiMapper<domain::models::Dependency, models::DependencyUiModel>>& dependencyUiMapper
):
	window(window),
	mapperFactory(mapperFactory),
	dependencyUiMapper(dependencyUiMapper)
{
	window->updateState(std::make_shared<states::EmptyState>());
}

MainWindowViewModel::~MainWindowViewModel()
{
	if (loadingThread.joinable()) {
		loadingThread.detach();
	}
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
			const auto& uiModels = dependencyUiMapper->map(dependencies);

			window->updateState(std::make_shared<states::SuccessState>(uiModels));
		} catch (std::exception& e) {
			window->updateState(std::make_shared<states::ErrorState>(e.what()));
		}
	});
}
