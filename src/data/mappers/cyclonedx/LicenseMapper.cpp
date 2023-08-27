#include "data/mappers/cyclonedx/LicenseMapper.hpp"

using namespace id::data::mappers::cyclonedx;

std::list<std::shared_ptr<models::License>> LicenseMapper::map(nlohmann::json json)
{
	auto licenses = std::list<std::shared_ptr<models::License>>();

	for (const auto& object: json) {
		if (object.contains(JSON_KEY_LICENSE) && !object.value(JSON_KEY_LICENSE, nlohmann::json()).empty()) {
			const auto& license = mapLicense(object.value(JSON_KEY_LICENSE, nlohmann::json()));
			licenses.emplace_back(license);
		}
	}

	return licenses;
}

std::shared_ptr<models::License> LicenseMapper::mapLicense(nlohmann::json json)
{
	const auto& license = std::make_shared<models::License>();

	// Check if the license is either an id or a name
	if (json.contains(JSON_KEY_ID)) {
		license->name = json.value(JSON_KEY_ID, std::string());
	} else {
		license->name = json.value(JSON_KEY_NAME, std::string());
	}

	license->url = json.value(JSON_KEY_URL, std::string());

	return license;
}