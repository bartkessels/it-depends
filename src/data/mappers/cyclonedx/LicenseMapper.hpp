#pragma once

#include <memory>
#include <list>
#include <string>
#include <nlohmann/json.hpp>

#include "domain/models/License.hpp"

using namespace id::domain;

namespace id::data::mappers::cyclonedx
{
	/**
	 * Map a json object with licenses to a generic list of Licenses.
	 *
	 */
	class LicenseMapper
	{
		public:
			~LicenseMapper() = default;

			std::list<std::shared_ptr<models::License>> mapLicenses(nlohmann::json json);

		private:
			inline static const std::string JSON_KEY_LICENSE = "license";
			inline static const std::string JSON_KEY_ID = "id";
			inline static const std::string JSON_KEY_NAME = "name";
			inline static const std::string JSON_KEY_URL = "url";

			std::shared_ptr<models::License> mapLicense(nlohmann::json json);
	};
}