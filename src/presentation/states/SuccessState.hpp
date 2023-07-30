#pragma once

#include <memory>

#include "presentation/states/MainWindowState.hpp"

namespace id::presentation::states
{
	struct SuccessState: public MainWindowState
	{
		public:
			~SuccessState() override = default;
	};
}