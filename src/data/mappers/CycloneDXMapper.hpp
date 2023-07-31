#pragma once

#include <memory>
#include <list>
#include <string>
#include <nlohmann/json.hpp>

#include "data/contracts/IFileReader.hpp"
#include "data/contracts/IMapper.hpp"
#include "domain/models/Dependency.hpp"
#include "domain/models/Url.hpp"
#include "domain/models/UrlType.hpp"

using namespace id::domain;

namespace id::data::mappers
{
	/**
	 * Map the specific CycloneDX SBOM to a generic list of Dependencies
	 */
	class CycloneDXMapper: public contracts::IMapper
	{
		public:
			CycloneDXMapper(std::shared_ptr<contracts::IFileReader> fileReader);
			~CycloneDXMapper() override = default;

			std::list<std::shared_ptr<models::Dependency>> map(std::string filePath) override;

		private:
			std::shared_ptr<contracts::IFileReader> fileReader;

			std::list<std::shared_ptr<models::Dependency>> mapDependencies(nlohmann::json json);
			std::shared_ptr<models::Dependency> mapDependency(nlohmann::json json);
			std::list<std::shared_ptr<models::Url>> mapUrls(nlohmann::json json);
			std::shared_ptr<models::Url> mapUrl(nlohmann::json json);
	};
}