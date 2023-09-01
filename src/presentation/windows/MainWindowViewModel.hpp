#pragma once

#include <future>
#include <memory>
#include <utility>

#include "data/contracts/IMapperFactory.hpp"
#include "presentation/contracts/IUiMapper.hpp"
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
				std::shared_ptr<data::contracts::IMapperFactory> mapperFactory
			);
			~MainWindowViewModel();

			void loadSBOM(domain::SbomType type, const std::string& fileLocation) override;

		private:
			std::shared_ptr<IMainWindow> window;
			std::shared_ptr<data::contracts::IMapperFactory> mapperFactory;
			std::thread loadingThread;
	};
}