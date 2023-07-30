#pragma once

#include "presentation/states/MainWindowState.hpp"

namespace id::presentation::states
{
	/**
 	 * Loading state for the MainWindow.
	 *
	 * This states represents any operation that requires the UI to display
	 * that something is loading.
	 */
	struct LoadingState: public MainWindowState
	{
		public:
			~LoadingState() override = default;
	};
}