#pragma once

#include <memory>
#include <list>

#include "data/contracts/IFileReaderFactory.hpp"
#include "data/contracts/IMapper.hpp"
#include "data/contracts/IMapperFactory.hpp"
#include "data/mappers/CycloneDXMapper.hpp"
#include "domain/SbomType.hpp"

namespace id::data::factories
{
	/**
	 * Factory to create instances of mappers based on the SBOM type
	 */
	class MapperFactory: public contracts::IMapperFactory
	{
		public:
			MapperFactory(std::shared_ptr<contracts::IFileReaderFactory> fileReaderFactory);
			~MapperFactory() override = default;

			std::shared_ptr<contracts::IMapper> getMapper(domain::SbomType type) override;

		private:
			std::shared_ptr<contracts::IFileReaderFactory> fileReaderFactory;
	};
}