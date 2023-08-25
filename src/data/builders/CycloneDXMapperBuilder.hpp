#pragma once

#include <memory>

#include "data/contracts/IFileReader.hpp"
#include "data/contracts/IMapper.hpp"
#include "data/contracts/IMapperBuilder.hpp"
#include "data/mappers/cyclonedx/DependencyMapper.hpp"
#include "data/mappers/cyclonedx/HashMapper.hpp"
#include "data/mappers/cyclonedx/LicenseMapper.hpp"
#include "data/mappers/cyclonedx/UrlMapper.hpp"
#include "data/mappers/cyclonedx/UrlTypeMapper.hpp"
#include "data/mappers/CycloneDXMapper.hpp"

namespace id::data::builders
{
	class CycloneDXMapperBuilder: public contracts::IMapperBuilder
	{
		public:
			~CycloneDXMapperBuilder() override = default;

			std::shared_ptr<contracts::IMapper> buildMapper(std::shared_ptr<contracts::IFileReader> fileReader) override;
	};
}