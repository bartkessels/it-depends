#pragma once

#include <memory>
#include <list>
#include <string>
#include <nlohmann/json.hpp>
#include <utility>

#include "data/contracts/IJsonMapper.hpp"
#include "domain/models/Dependency.hpp"

using namespace id::domain;

namespace id::data::mappers::cyclonedx
{
	/**
	 * Map CycloneDX based SBOM to a generic list of Dependencies
	 */
	class DependencyMapper: public contracts::IJsonMapper<std::list<std::shared_ptr<models::Dependency>>>
	{
		public:
			explicit DependencyMapper(
				std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::Hash>>>> hashMapper,
				std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::License>>>> licenseMapper,
				std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::Url>>>> urlMapper
			);

			auto map(const nlohmann::json& json) -> std::list<std::shared_ptr<models::Dependency>> override;

		private:
			inline static const std::string JSON_KEY_PARENT = "component";
			inline static const std::string JSON_KEY_DEPENDENCIES = "components";
			inline static const std::string JSON_KEY_ID = "bom-ref";
			inline static const std::string JSON_KEY_NAME = "name";
			inline static const std::string JSON_KEY_DESCRIPTION = "description";
			inline static const std::string JSON_KEY_VERSION = "version";
			inline static const std::string JSON_KEY_HASHES = "hashes";
			inline static const std::string JSON_KEY_LICENSES = "licenses";
			inline static const std::string JSON_KEY_URLS = "externalReferences";
			inline static const std::string JSON_KEY_DEPENDENCY_TREE = "dependencies";
			inline static const std::string JSON_KEY_DEPENDENCY_TREE_ID = "ref";
			inline static const std::string JSON_KEY_DEPENDENCY_TREE_DEPENDENCIES = "dependsOn";

			std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::Hash>>>> hashMapper;
			std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::License>>>> licenseMapper;
			std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::Url>>>> urlMapper;

			auto mapDependency(const nlohmann::json& json) -> std::shared_ptr<models::Dependency>;
			auto buildDependency(const nlohmann::json& json, const std::string& id) -> std::shared_ptr<models::Dependency>;
			auto buildDependencyTree(const nlohmann::json& json, const std::string& parentId) -> std::list<std::shared_ptr<models::Dependency>>;
	};
}
