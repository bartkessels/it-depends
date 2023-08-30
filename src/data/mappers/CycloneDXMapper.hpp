#pragma once

#include <memory>
#include <list>
#include <string>
#include <nlohmann/json.hpp>

#include "data/contracts/IFileReader.hpp"
#include "data/contracts/IMapper.hpp"
#include "data/mappers/cyclonedx/DependencyMapper.hpp"
#include "domain/models/Dependency.hpp"

using namespace id::domain;

namespace id::data::mappers
{
	/**
	 * Map the specific CycloneDX SBOM to a generic list of Dependencies
	 */
	class CycloneDXMapper: public contracts::IMapper
	{
		public:
			CycloneDXMapper(
				  std::shared_ptr<contracts::IFileReader> fileReader,
				  std::shared_ptr<cyclonedx::DependencyMapper> dependencyMapper
			 );

			auto map(const std::string& filePath) -> std::list<std::shared_ptr<models::Dependency>> override;

		private:
			std::shared_ptr<contracts::IFileReader> fileReader;
			std::shared_ptr<cyclonedx::DependencyMapper> dependencyMapper;
	};
}