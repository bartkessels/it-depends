#include "data/mappers/cyclonedx/UrlTypeMapper.hpp"

using namespace id::data::mappers::cyclonedx;

models::UrlType UrlTypeMapper::map(std::string type)
{
	if (type == URL_TYPE_ISSUE_TRACKER) {
		return models::UrlType::IssueTracker;
	} else if (type == URL_TYPE_VCS) {
		return models::UrlType::VCS;
	}

	// Default value for an url type is Website
	return models::UrlType::Website;
}