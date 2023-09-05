#pragma once

#include <memory>
#include <vector>

namespace id::presentation::contracts
{
	/**
	 * Map a domain model to a corresponding UiModel.
	 *
	 * This interface is designed so all complex logic for the properties
	 * that need to be calculated before being shown, can be abstracted away.
	 *
	 * @tparam Model the regular model that is used in the domain and data layer
	 * @tparam UiModel the UI model that is going to be mapped onto the actual UI
	 */
	template <typename Model, typename UiModel>
	struct IUiMapper
	{
		public:
			virtual auto map(const std::vector<std::shared_ptr<Model>>& models) -> std::vector<std::shared_ptr<UiModel>> = 0;
	};
}