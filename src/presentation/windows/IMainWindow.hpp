#pragma once

#include <memory>

#include "presentation/states/MainWindowState.hpp"
#include "presentation/windows/IMainWindowViewModel.hpp"

namespace id::presentation::windows
{
    struct IMainWindow
    {
    	public:
        	virtual ~IMainWindow() = default;

        	virtual void setViewModel(std::shared_ptr<IMainWindowViewModel> viewModel) = 0;
        	virtual void updateState(std::shared_ptr<states::MainWindowState> newState) = 0;
    };
}