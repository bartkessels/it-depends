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

        	virtual void setViewModel(const std::shared_ptr<IMainWindowViewModel>& viewModel) = 0;
        	virtual void updateState(const std::shared_ptr<states::MainWindowState>& newState) = 0;
    };
}