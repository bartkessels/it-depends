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

	for (const auto& object: json.value(JSON_KEY_DEPENDENCIES, nlohmann::json())) {
		if (!object.empty()) {
			const auto& dependency = mapDependency(object);
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
	dependency->dependencies = this->buildDependencyTree(json, dependency->id);

	return dependency;
}

auto DependencyMapper::buildDependencyTree(const nlohmann::json& json, const std::string& parentId) -> std::list<std::shared_ptr<models::Dependency>> {
	auto dependenciesForParent = std::list<std::shared_ptr<models::Dependency>>();

	for (const auto& object: json.value(JSON_KEY_DEPENDENCY_TREE, nlohmann::json())) {
		if (!object.empty() && object.value(JSON_KEY_DEPENDENCY_TREE_ID, std::string()) == parentId) {
			for (const auto& depObj: object.value(JSON_KEY_DEPENDENCY_TREE_DEPENDENCIES, nlohmann::json())) {
				const auto& dep = buildDependency(json, depObj.value(JSON_KEY_DEPENDENCY_TREE_ID, std::string()));
				dep->dependencies.emplace_back(dep);

				dependenciesForParent.emplace_back(dep);
			}
		}
	}

	return dependenciesForParent;
}

auto DependencyMapper::buildDependency(const nlohmann::json& json, const std::string& id) -> std::shared_ptr<models::Dependency>
{
	for (const auto& object: json) {
		if (!object.empty() && json.value(JSON_KEY_ID, std::string()) == id) {
			return mapDependency(object);
		}
	}

	return {};
}