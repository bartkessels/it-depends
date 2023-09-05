#pragma once

#include <string>
#include <vector>

#include "domain/models/Dependency.hpp"

using namespace id::domain;

namespace id::data::contracts
{
	struct IMapper
	{
		public:
			virtual auto map(const std::string& filePath) -> std::vector<std::shared_ptr<models::Dependency>> = 0;
	};
}