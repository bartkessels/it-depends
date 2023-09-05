#pragma once

#include <vector>
#include <memory>

#include "presentation/models/DependencyUiModel.hpp"
#include "presentation/states/MainWindowState.hpp"

using namespace id::domain;

namespace id::presentation::states
{
	/**
 	 * Success state for the MainWindow.
	 *
	 * This states represents the successful reading of the SBOM file and
	 * mapping the dependencies into a generic dependency list.
	 *
	 */
	struct SuccessState: public MainWindowState
	{
		public:
			explicit SuccessState(const std::vector<std::shared_ptr<models::DependencyUiModel>>& dependencies):
				dependencies(dependencies) {}
			~SuccessState() override = default;

			std::vector<std::shared_ptr<models::DependencyUiModel>> dependencies;
	};
}