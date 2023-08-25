#pragma once

#include <memory>

#include "data/contracts/IFileReaderFactory.hpp"
#include "data/contracts/IMapper.hpp"
#include "data/contracts/IMapperFactory.hpp"
#include "data/mappers/cyclonedx/DependencyMapper.hpp"
#include "data/mappers/cyclonedx/HashMapper.hpp"
#include "data/mappers/cyclonedx/LicenseMapper.hpp"
#include "data/mappers/cyclonedx/UrlMapper.hpp"
#include "data/mappers/CycloneDXMapper.hpp"

namespace id::data::factories
{
	/**
	 * Factory to create a mapper instance of the CycloneDX mapper(s).
	 *
	 */
	class CycloneDXMapperFactory: public contracts::IMapperFactory
	{
		public:
			explicit CycloneDXMapperFactory(std::shared_ptr<contracts::IFileReaderFactory> fileReaderFactory);
			~CycloneDXMapperFactory() override = default;

			std::shared_ptr<contracts
	};
}