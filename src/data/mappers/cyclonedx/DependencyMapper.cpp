#include "data/mappers/cyclonedx/DependencyMapper.hpp"

using namespace id::data::mappers::cyclonedx;

DependencyMapper::DependencyMapper(
	std::shared_ptr<HashMapper> hashMapper,
	std::shared_ptr<LicenseMapper> licenseMapper,
	std::shared_ptr<UrlMapper> urlMapper
):
	hashMapper(hashMapper),
	licenseMapper(licenseMapper),
	urlMapper(urlMapper)
{

}

std::list<std::shared_ptr<models::Dependency>> DependencyMapper::mapDependencies(nlohmann::json json)
{
	auto dependencies = std::list<std::shared_ptr<models::Dependency>>();

	for (const auto& object: json[JSON_KEY_DEPENDENCIES]) {
		const auto& dependency = mapDependency(object);
		dependencies.emplace_back(dependency);
	}

	return dependencies;
}

std::shared_ptr<models::Dependency> DependencyMapper::mapDependency(nlohmann::json json)
{
	const auto& dependency = std::make_shared<models::Dependency>();

	dependency->id = json.value(JSON_KEY_ID, std::string());
	dependency->name = json.value(JSON_KEY_NAME, std::string());
	dependency->version = json.value(JSON_KEY_VERSION, std::string());

	if (json.contains(JSON_KEY_HASHES)) {
		dependency->hashes = hashMapper->mapHashes(json.value(JSON_KEY_HASHES, std::string()));
	}

	if (json.contains(JSON_KEY_LICENSES)) {
		dependency->licenses = licenseMapper->mapLicenses(json.value(JSON_KEY_LICENSES, std::string()));
	}

	if (json.contains(JSON_KEY_URLS)) {
		dependency->urls = urlMapper->mapUrls(json.value(JSON_KEY_URLS, std::string()));
	}

	return dependency;
}