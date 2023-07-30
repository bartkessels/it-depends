#pragma once

#include "presentation/states/MainWindowState.hpp"

namespace id::presentation::states
{
	/**
 	 * Empty state for the MainWindow.
 	 *
 	 * This is used when the MainWindow doesn't have an active state.
 	 * This can be used as the default state.
 	 */
	struct EmptyState: public MainWindowState
	{
		public:
			~EmptyState() override = default;
	};
}
