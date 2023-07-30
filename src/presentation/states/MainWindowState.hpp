#pragma once

namespace id::presentation::states
{
	/**
	 * Abstract state for the main window.
	 *
	 * The implementations of this state should be reflected in the MainWindow ui.
	 */
	struct MainWindowState
	{
		public:
			virtual ~MainWindowState() = default;
	};
}