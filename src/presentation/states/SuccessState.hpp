#pragma once

#include <list>
#include <memory>

#include "domain/models/Dependency.hpp"
#include "presentation/states/MainWindowState.hpp"

using namespace id::domain;

namespace id::presentation::states
{
	struct SuccessState: public MainWindowState
	{
		public:
			explicit SuccessState(std::list<std::shared_ptr<models::Dependency>> dependencies):
				dependencies(dependencies) {}
			~SuccessState() override = default;

			std::list<std::shared_ptr<models::Dependency>> dependencies;
	};
}