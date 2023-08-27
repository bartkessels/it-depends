#include "data/mappers/cyclonedx/DependencyMapper.hpp"

using namespace id::data;
using namespace id::data::mappers::cyclonedx;
using namespace id::domain::models;

DependencyMapper::DependencyMapper(
	std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<Hash>>>> hashMapper,
	std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<License>>>> licenseMapper,
	std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<Url>>>> urlMapper
):
	hashMapper(hashMapper),
	licenseMapper(licenseMapper),
	urlMapper(urlMapper)
{

}

std::list<std::shared_ptr<models::Dependency>> DependencyMapper::map(nlohmann::json json)
{
	auto dependencies = std::list<std::shared_ptr<models::Dependency>>();

	for (const auto& object: json) {
		if (!object.empty()) {
			const auto& dependency = mapDependency(object);
			dependencies.emplace_back(dependency);
		}
	}

	return dependencies;
}

std::shared_ptr<models::Dependency> DependencyMapper::mapDependency(nlohmann::json json)
{
	const auto& dependency = std::make_shared<models::Dependency>();

	dependency->id = json.value(JSON_KEY_ID, std::string());
	dependency->name = json.value(JSON_KEY_NAME, std::string());
	dependency->version = json.value(JSON_KEY_VERSION, std::string());
	dependency->description = json.value(JSON_KEY_DESCRIPTION, std::string());
	dependency->hashes = hashMapper->map(json.value(JSON_KEY_HASHES, nlohmann::json()));
	dependency->licenses = licenseMapper->map(json.value(JSON_KEY_LICENSES, nlohmann::json()));
	dependency->urls = urlMapper->map(json.value(JSON_KEY_URLS, nlohmann::json()));

	return dependency;
}