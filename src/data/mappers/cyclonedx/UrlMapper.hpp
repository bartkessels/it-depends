#pragma once

#include <memory>
#include <list>
#include <string>
#include <nlohmann/json.hpp>

#include "data/mappers/cyclonedx/UrlTypeMapper.hpp"
#include "domain/models/Url.hpp"
#include "domain/models/UrlType.hpp"

using namespace id::domain;

namespace id::data::mappers::cyclonedx
{
	/**
	 * Map a json object with urls to a generic list of Urls.
	 *
	 * Only map the json object to a Url when both the type and
	 * url have a value. Otherwise there's no need to parse the
	 * json object because it cannot be properly displayed.
	 */
	class UrlMapper
	{
		public:
			explicit UrlMapper(std::shared_ptr<UrlTypeMapper> urlTypeMapper);
			~UrlMapper() = default;

			std::list<std::shared_ptr<models::Url>> mapUrls(nlohmann::json json);

		private:
			inline static const std::string JSON_KEY_URL_TYPE = "type";
			inline static const std::string JSON_KEY_URL = "url";

			std::shared_ptr<UrlTypeMapper> urlTypeMapper;

			std::shared_ptr<models::Url> mapUrl(nlohmann::json json);
	};
}