#pragma once

#include <string>
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
			virtual ~IMapperFactory() = default;

			virtual std::shared_ptr<IMapper> getMapper(domain::SbomType type) = 0;
	};
}