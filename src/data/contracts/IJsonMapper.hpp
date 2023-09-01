#pragma once

#include <nlohmann/json.hpp>

namespace id::data::contracts
{
	template <typename T>
	struct IJsonMapper
	{
		public:
			virtual auto map(const nlohmann::json& json) -> T = 0;
	};
}