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
			virtual auto build(domain::SbomType type) -> std::shared_ptr<contracts::IMapperBuilder> = 0;
	};
}