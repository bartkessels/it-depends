#pragma once

#include <memory>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <utility>

#include "data/contracts/IJsonMapper.hpp"
#include "domain/models/Author.hpp"
#include "domain/models/Dependency.hpp"
#include "domain/models/Type.hpp"

using namespace id::domain;

namespace id::data::mappers::cyclonedx
{
	/**
	 * Create alias for readability of the code.
	 */
	using DependencyPtrList = std::vector<std::shared_ptr<models::Dependency>>;

	/**
	 * Map CycloneDX based SBOM to a generic list of Dependencies
	 */
	class DependencyMapper: public contracts::IJsonMapper<DependencyPtrList>
	{
		public:
			explicit DependencyMapper(
				std::shared_ptr<contracts::IJsonMapper<std::vector<std::shared_ptr<models::Hash>>>> hashMapper,
				std::shared_ptr<contracts::IJsonMapper<std::vector<std::shared_ptr<models::License>>>> licenseMapper,
				std::shared_ptr<contracts::IJsonMapper<std::vector<std::shared_ptr<models::Url>>>> urlMapper
			);

			auto map(const nlohmann::json& json) -> DependencyPtrList override;

		private:
			inline static const std::string JSON_KEY_PARENT = "component";
			inline static const std::string JSON_KEY_COMPONENTS = "components";
			inline static const std::string JSON_KEY_ID = "bom-ref";
			inline static const std::string JSON_KEY_TYPE = "type";
			inline static const std::string JSON_KEY_NAME = "name";
			inline static const std::string JSON_KEY_PUBLISHER = "publisher";
			inline static const std::string JSON_KEY_DESCRIPTION = "description";
			inline static const std::string JSON_KEY_VERSION = "version";
			inline static const std::string JSON_KEY_HASHES = "hashes";
			inline static const std::string JSON_KEY_LICENSES = "licenses";
			inline static const std::string JSON_KEY_URLS = "externalReferences";
			inline static const std::string JSON_KEY_DEPENDENCIES = "dependencies";
			inline static const std::string JSON_KEY_DEPENDENCY_ID = "ref";
			inline static const std::string JSON_KEY_DEPENDENCY_DEPENDS_ON = "dependsOn";

			std::shared_ptr<contracts::IJsonMapper<std::vector<std::shared_ptr<models::Hash>>>> hashMapper;
			std::shared_ptr<contracts::IJsonMapper<std::vector<std::shared_ptr<models::License>>>> licenseMapper;
			std::shared_ptr<contracts::IJsonMapper<std::vector<std::shared_ptr<models::Url>>>> urlMapper;

			auto mapDependency(const nlohmann::json& json) -> std::shared_ptr<models::Dependency>;
			static auto mapAuthor(const nlohmann::json& json) -> std::shared_ptr<models::Author>;
			static auto mapType(const std::string& type) -> models::Type;
			static auto mapTransitiveDependencies(const nlohmann::json& json, const DependencyPtrList& dependencies) -> DependencyPtrList;
			static auto findDependency(const DependencyPtrList& dependencies, const std::string& id) -> std::shared_ptr<models::Dependency>;
	};
}
