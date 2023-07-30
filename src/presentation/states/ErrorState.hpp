#pragma once

#include <string>

#include "presentation/states/MainWindowState.hpp"

namespace id::presentation::states
{
	/**
 	 * Error state for the MainWindow.
 	 *
 	 * This state is used to represent some sort of error. It includes a property
 	 * which can contain the error message.
 	 */
	struct ErrorState: public MainWindowState
	{
		public:
			~ErrorState() override = default;

			std::string message;
	};
}
