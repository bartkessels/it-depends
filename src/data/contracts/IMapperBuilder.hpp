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

			virtual std::shared_ptr<IMapper> buildMapper(std::shared_ptr<IFileReader> fileReader) = 0;
	};
}