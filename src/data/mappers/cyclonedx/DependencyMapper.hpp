#pragma once

#include <memory>
#include <list>
#include <string>
#include <nlohmann/json.hpp>

#include "data/mappers/cyclonedx/HashMapper.hpp"
#include "data/mappers/cyclonedx/LicenseMapper.hpp"
#include "data/mappers/cyclonedx/UrlMapper.hpp"
#include "domain/models/Dependency.hpp"

using namespace id::domain;

namespace id::data::mappers::cyclonedx
{
	/**
	 * Map CycloneDX based SBOM to a generic list of Dependencies
	 */
	class DependencyMapper
	{
		public:
			explicit DependencyMapper(
					 std::shared_ptr<HashMapper> hashMapper,
					 std::shared_ptr<LicenseMapper> licenseMapper,
					 std::shared_ptr<UrlMapper> urlMapper
				);
			~DependencyMapper() = default;

			std::list<std::shared_ptr<models::Dependency>> mapDependencies(nlohmann::json json);

		private:
			inline static const std::string JSON_KEY_DEPENDENCIES = "components";
			inline static const std::string JSON_KEY_ID = "bom-ref";
			inline static const std::string JSON_KEY_NAME = "name";
			inline static const std::string JSON_KEY_VERSION = "version";
			inline static const std::string JSON_KEY_HASHES = "hashes";
			inline static const std::string JSON_KEY_LICENSES = "licenses";
			inline static const std::string JSON_KEY_URLS = "externalReferences";

			std::shared_ptr<HashMapper> hashMapper;
			std::shared_ptr<LicenseMapper> licenseMapper;
			std::shared_ptr<UrlMapper> urlMapper;

			std::shared_ptr<models::Dependency> mapDependency(nlohmann::json json);
	};
}
