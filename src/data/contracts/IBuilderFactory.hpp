#pragma once

#include <memory>

#include "data/contracts/IMapperBuilder.hpp"
#include "domain/SbomType.hpp"

namespace id::data::contracts
{
	/**
	 * Interface to create a builder for a specific SBOM type.
	 *
	 */
	struct IBuilderFactory
	{
		public:
			virtual ~IBuilderFactory() = default;

			virtual std::shared_ptr<IMapperBuilder> build(domain::SbomType type) = 0;
	};
}