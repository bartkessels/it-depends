#pragma once

#include <memory>

#include "data/contracts/IFileReader.hpp"
#include "data/contracts/IMapper.hpp"

namespace id::data::contracts
{
	struct IMapperBuilder
	{
		public:
			virtual ~IMapperBuilder() = default;

			virtual std::shared_ptr<IMapper> build(std::shared_ptr<contracts::IFileReader> fileReader) = 0;
	};
}