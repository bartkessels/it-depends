#include "data/builders/CycloneDXMapperBuilder.hpp"

using namespace id::data;
using namespace id::data::builders;
using namespace id::data::mappers::cyclonedx;

std::shared_ptr<contracts::IMapper> CycloneDXMapperBuilder::buildMapper(std::shared_ptr<contracts::IFileReader> fileReader)
{
	const auto& hashMapper = std::make_shared<HashMapper>();
	const auto& licenseMapper = std::make_shared<LicenseMapper>();
	const auto& urlTypeMapper = std::make_shared<UrlTypeMapper>();
	const auto& urlMapper = std::make_shared<UrlMapper>(urlTypeMapper);
	const auto& dependencyMapper = std::make_shared<DependencyMapper>(
		hashMapper,
		licenseMapper,
		urlMapper
	);

	return std::make_shared<mappers::CycloneDXMapper>(
		fileReader,
		dependencyMapper
	);
}