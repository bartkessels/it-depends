#include "data/mappers/cyclonedx/DependencyMapper.hpp"

using namespace id::data;
using namespace id::data::mappers::cyclonedx;
using namespace id::domain;

DependencyMapper::DependencyMapper(
	std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::Hash>>>> hashMapper,
	std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::License>>>> licenseMapper,
	std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::Url>>>> urlMapper
):
	hashMapper(std::move(hashMapper)),
	licenseMapper(std::move(licenseMapper)),
	urlMapper(std::move(urlMapper))
{

}

auto DependencyMapper::map(const nlohmann::json& json) -> std::list<std::shared_ptr<models::Dependency>>
{
	auto dependencies = std::list<std::shared_ptr<models::Dependency>>();

	for (const auto& object: json.value(JSON_KEY_COMPONENTS, nlohmann::json())) {
		if (!object.empty()) {
			const auto& dependency = mapDependency(object);
			dependency->dependencies = mapDependencies(json, dependency->id);
			dependencies.emplace_back(dependency);
		}
	}

	return dependencies;
}

auto DependencyMapper::mapDependency(const nlohmann::json& json) -> std::shared_ptr<models::Dependency>
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

auto DependencyMapper::mapDependencies(const nlohmann::json& json, const std::string& dependencyId) -> std::list<std::shared_ptr<models::Dependency>>
{
	auto dependencies = std::list<std::shared_ptr<models::Dependency>>();
	const auto& allJsonDependencies = json.value(JSON_KEY_DEPENDENCIES, nlohmann::json());

	for (const auto& jsonDependency : allJsonDependencies) {
		const auto& currentDependencyId = jsonDependency.value(JSON_KEY_DEPENDENCY_ID, std::string());

		if (currentDependencyId == dependencyId) {
			const auto& dependsOnArray = jsonDependency.value(JSON_KEY_DEPENDENCY_DEPENDS_ON, nlohmann::json());
			for (const auto& dependsOnRef: dependsOnArray) {
				const auto& dependency = buildDependency(json, dependsOnRef.get<std::string>());
				dependency->dependencies = mapDependencies(json, dependency->id);
				dependencies.emplace_back(dependency);
			}
		}
	}

	return dependencies;
}

auto DependencyMapper::buildDependency(const nlohmann::json& json, const std::string& id) -> std::shared_ptr<models::Dependency>
{
	const auto& dependencies = json.value(JSON_KEY_COMPONENTS, nlohmann::json());

	for (const auto& object: dependencies) {
		const auto& dependencyId = object.value(JSON_KEY_ID, std::string());

		if (!object.empty() && dependencyId == id) {
			return mapDependency(object);
		}
	}

	return {};
}