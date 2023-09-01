#pragma once

#include <vector>
#include <memory>

#include "domain/models/Dependency.hpp"
#include "presentation/states/MainWindowState.hpp"

using namespace id::domain;

namespace id::presentation::states
{
	struct SuccessState: public MainWindowState
	{
		public:
			explicit SuccessState(std::vector<std::shared_ptr<domain::models::Dependency>> dependencies):
				dependencies(dependencies) {}
			~SuccessState() override = default;

			std::vector<std::shared_ptr<domain::models::Dependency>> dependencies;
	};
}