#pragma once

#include <memory>

#include "data/builders/CycloneDXMapperBuilder.hpp"
#include "data/contracts/IBuilderFactory.hpp"
#include "data/contracts/IMapperBuilder.hpp"
#include "data/exceptions/UnsupportedSBOMTypeException.hpp"
#include "domain/SbomType.hpp"

namespace id::data::factories
{
	/**
	 * Create an instance of a specific builder based on the
	 * SBOM type.
	 *
	 */
	class BuilderFactory: public contracts::IBuilderFactory
	{
		public:
			~BuilderFactory() override = default;

			std::shared_ptr<contracts::IMapperBuilder> build(domain::SbomType type) override;
	};
}