#pragma once

#include <memory>
#include <nlohmann/json.hpp>

namespace id::data::contracts
{
	template <typename T>
	struct IJsonMapper
	{
		public:
			virtual ~IJsonMapper() = default;
			virtual T map(nlohmann::json json) = 0;
	};
}