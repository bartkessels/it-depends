#pragma once

#include <memory>

#include "data/contracts/IFileReader.hpp"
#include "data/contracts/IMapper.hpp"

namespace id::data::contracts
{
	struct IMapperBuilder
	{
		public:
			virtual auto build(const std::shared_ptr<contracts::IFileReader>& fileReader) -> std::shared_ptr<contracts::IMapper> = 0;
	};

}