#pragma once

#include <memory>
#include <list>
#include <string>

#include "domain/models/Dependency.hpp"

using namespace id::domain;

namespace id::data::contracts
{
	struct IMapper
	{
		public:
			virtual ~IMapper() = default;

			virtual std::list<std::shared_ptr<models::Dependency>> map(std::string filePath) = 0;
	};
}