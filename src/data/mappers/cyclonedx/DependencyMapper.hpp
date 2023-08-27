#pragma once

#include <memory>
#include <list>
#include <string>
#include <nlohmann/json.hpp>

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
			~DependencyMapper() override = default;

			std::list<std::shared_ptr<models::Dependency>> map(nlohmann::json json) override;

		private:
			inline static const std::string JSON_KEY_DEPENDENCIES = "components";
			inline static const std::string JSON_KEY_ID = "bom-ref";
			inline static const std::string JSON_KEY_NAME = "name";
			inline static const std::string JSON_KEY_DESCRIPTION = "description";
			inline static const std::string JSON_KEY_VERSION = "version";
			inline static const std::string JSON_KEY_HASHES = "hashes";
			inline static const std::string JSON_KEY_LICENSES = "licenses";
			inline static const std::string JSON_KEY_URLS = "externalReferences";

			std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::Hash>>>> hashMapper;
			std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::License>>>> licenseMapper;
			std::shared_ptr<contracts::IJsonMapper<std::list<std::shared_ptr<models::Url>>>> urlMapper;

			std::shared_ptr<models::Dependency> mapDependency(nlohmann::json json);
	};
}
