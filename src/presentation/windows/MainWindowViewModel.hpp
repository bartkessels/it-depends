#pragma once

#include <future>
#include <memory>

#include "data/contracts/IMapperFactory.hpp"
#include "domain/models/Dependency.hpp"
#include "presentation/contracts/IUiMapper.hpp"
#include "presentation/models/DependencyUiModel.hpp"
#include "presentation/states/EmptyState.hpp"
#include "presentation/states/ErrorState.hpp"
#include "presentation/states/LoadingState.hpp"
#include "presentation/states/SuccessState.hpp"
#include "presentation/states/MainWindowState.hpp"
#include "presentation/windows/IMainWindowViewModel.hpp"
#include "presentation/windows/IMainWindow.hpp"

namespace id::presentation::windows
{
	class MainWindowViewModel: public IMainWindowViewModel
	{
		public:
			explicit MainWindowViewModel(
				const std::shared_ptr<IMainWindow>& window,
				const std::shared_ptr<data::contracts::IMapperFactory>& mapperFactory,
				const std::shared_ptr<contracts::IUiMapper<domain::models::Dependency, models::DependencyUiModel>>& dependencyUiMapper
			);
			~MainWindowViewModel();

			void loadSBOM(domain::SbomType type, const std::string& fileLocation) override;

			/**
			 * Define the loading thread public so we can access
			 * it from the test cases. This makes sure we are able
			 * to make correct assertions about the working of the
			 * ViewModel.
			 *
			 */
			std::thread loadingThread;

		private:
			std::shared_ptr<IMainWindow> window;
			std::shared_ptr<data::contracts::IMapperFactory> mapperFactory;
			std::shared_ptr<contracts::IUiMapper<domain::models::Dependency, models::DependencyUiModel>> dependencyUiMapper;
	};
}