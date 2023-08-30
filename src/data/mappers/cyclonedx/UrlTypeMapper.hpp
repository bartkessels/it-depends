#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "domain/models/UrlType.hpp"

using namespace id::domain;

namespace id::data::mappers::cyclonedx
{
	/**
	 * Map a string to a specific UrlType.
	 *
	 * Map a cyclone url type to a generic UrlType object.
	 */
	class UrlTypeMapper
	{
		public:
			auto map(const std::string& type) -> models::UrlType;

		private:
			inline static const std::string URL_TYPE_ISSUE_TRACKER = "issue-tracker";
			inline static const std::string URL_TYPE_VCS = "vcs";
	};
}