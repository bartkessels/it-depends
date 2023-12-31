#pragma once

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
			 auto build(const std::shared_ptr<contracts::IFileReader>& fileReader) -> std::shared_ptr<contracts::IMapper> override;
	};
}