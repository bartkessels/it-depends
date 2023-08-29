#include "data/mappers/cyclonedx/UrlTypeMapper.hpp"

using namespace id::data::mappers::cyclonedx;

auto UrlTypeMapper::map(const std::string& type) -> models::UrlType
{
	if (type == URL_TYPE_ISSUE_TRACKER) {
		return models::UrlType::IssueTracker;
	} else if (type == URL_TYPE_VCS) {
		return models::UrlType::VCS;
	}

	// Default value for an url type is Website
	return models::UrlType::Website;
}