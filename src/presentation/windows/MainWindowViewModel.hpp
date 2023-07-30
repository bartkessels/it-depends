#pragma once

#include <memory>

#include "presentation/states/EmptyState.hpp"
#include "presentation/states/MainWindowState.hpp"
#include "presentation/windows/IMainWindowViewModel.hpp"
#include "presentation/windows/IMainWindow.hpp"

namespace id::presentation::windows
{
	class MainWindowViewModel: public IMainWindowViewModel
	{
		public:
			MainWindowViewModel(std::shared_ptr<IMainWindow> window);
			~MainWindowViewModel() = default;

			void loadSBOM(std::shared_ptr<domain::SbomType> type, std::string fileLocation) override;

		private:
			std::shared_ptr<IMainWindow> window;
	};
}