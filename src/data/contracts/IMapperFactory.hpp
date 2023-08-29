#pragma once

#include <memory>

#include "data/contracts/IMapper.hpp"
#include "domain/SbomType.hpp"

namespace id::data::contracts
{
	/**
	 * Get an instance of a Mapper based on the SBOM type
	 */
	struct IMapperFactory
	{
		public:
			virtual auto getMapper(domain::SbomType type) -> std::shared_ptr<contracts::IMapper> = 0;
	};
}