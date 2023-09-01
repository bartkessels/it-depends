#include "data/mappers/cyclonedx/DependencyMapper.hpp"

using namespace id::data;
using namespace id::data::mappers::cyclonedx;
using namespace id::domain;

DependencyMapper::DependencyMapper(
	std::shared_ptr<contracts::IJsonMapper<std::vector<std::shared_ptr<models::Hash>>>> hashMapper,
	std::shared_ptr<contracts::IJsonMapper<std::vector<std::shared_ptr<models::License>>>> licenseMapper,
	std::shared_ptr<contracts::IJsonMapper<std::vector<std::shared_ptr<models::Url>>>> urlMapper
):
	hashMapper(std::move(hashMapper)),
	licenseMapper(std::move(licenseMapper)),
	urlMapper(std::move(urlMapper))
{

}

auto DependencyMapper::map(const nlohmann::json& json) -> DependencyPtrList
{
	auto dependencies = DependencyPtrList();

	for (const auto& object: json.value(JSON_KEY_COMPONENTS, nlohmann::json())) {
		if (!object.empty()) {
			const auto& dependency = mapDependency(object);
			dependencies.emplace_back(dependency);
		}
	}

	this->mapTransitiveDependencies(json, dependencies);

	return dependencies;
}

auto DependencyMapper::mapDependency(const nlohmann::json& json) -> std::shared_ptr<models::Dependency>
{
	const auto& dependency = std::make_shared<models::Dependency>();

	dependency->id = json.value(JSON_KEY_ID, std::string());
	dependency->type = mapType(json.value(JSON_KEY_TYPE, std::string()));
	dependency->name = json.value(JSON_KEY_NAME, std::string());
	dependency->version = json.value(JSON_KEY_VERSION, std::string());
	dependency->description = json.value(JSON_KEY_DESCRIPTION, std::string());
	dependency->author = mapAuthor(json);
	dependency->hashes = hashMapper->map(json.value(JSON_KEY_HASHES, nlohmann::json()));
	dependency->licenses = licenseMapper->map(json.value(JSON_KEY_LICENSES, nlohmann::json()));
	dependency->urls = urlMapper->map(json.value(JSON_KEY_URLS, nlohmann::json()));

	return dependency;
}

auto DependencyMapper::mapAuthor(const nlohmann::json& json) -> std::shared_ptr<models::Author>
{
	if (json.contains(JSON_KEY_PUBLISHER)) {
		const auto& author = std::make_shared<models::Author>();

		author->name = json.value(JSON_KEY_PUBLISHER, std::string());

		/// Use empty values because this information is not available for CycloneDX
		author->emailAddress = std::string();
		author->website = std::string();

		return author;
	}

	return {};
}

auto DependencyMapper::mapType(const std::string& type) -> models::Type
{
	if (type == "library") {
		return models::Type::Library;
	} else if (type == "application") {
		return models::Type::Application;
	}

	return models::Type::Unknown;
}

auto DependencyMapper::findDependency(const id::data::mappers::cyclonedx::DependencyPtrList &dependencies, const std::string& id) -> std::shared_ptr<models::Dependency>
{
	return *std::find_if(dependencies.begin(), dependencies.end(), [&id](const std::shared_ptr<models::Dependency>& obj) {
		return obj->id == id;
	});
}

auto DependencyMapper::mapTransitiveDependencies(const nlohmann::json& json, const DependencyPtrList& dependencies) -> DependencyPtrList
{
	const auto& jsonDependencies = json.value(JSON_KEY_DEPENDENCIES, nlohmann::json());

	for (const auto& jsonDependency : jsonDependencies) {
		const auto& currentDependencyId = jsonDependency.value(JSON_KEY_DEPENDENCY_ID, std::string());

		for (const auto& dependency: dependencies) {
			if (dependency->id == currentDependencyId) {
				const auto& refs = jsonDependency.value(JSON_KEY_DEPENDENCY_DEPENDS_ON, nlohmann::json());

				for (const auto& ref: refs) {
					dependency->dependencies.emplace_back(findDependency(dependencies, ref.get<std::string>()));
				}
			}
		}
	}

	return dependencies;
}
