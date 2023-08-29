#pragma once

#include <memory>
#include <list>
#include <string>
#include <nlohmann/json.hpp>

#include "data/contracts/IJsonMapper.hpp"
#include "domain/models/License.hpp"

using namespace id::domain;

namespace id::data::mappers::cyclonedx
{
	/**
	 * Map a json object with licenses to a generic list of Licenses.
	 *
	 */
	class LicenseMapper: public contracts::IJsonMapper<std::list<std::shared_ptr<models::License>>>
	{
		public:
			auto map(const nlohmann::json& json) -> std::list<std::shared_ptr<models::License>> override;

		private:
			inline static const std::string JSON_KEY_LICENSE = "license";
			inline static const std::string JSON_KEY_ID = "id";
			inline static const std::string JSON_KEY_NAME = "name";
			inline static const std::string JSON_KEY_URL = "url";

			static auto mapLicense(const nlohmann::json& json) -> std::shared_ptr<models::License>;
	};
}