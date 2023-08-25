#include "data/mappers/cyclonedx/UrlMapper.hpp"

using namespace id::data::mappers::cyclonedx;

UrlMapper::UrlMapper(std::shared_ptr<UrlTypeMapper> urlTypeMapper):
	urlTypeMapper(urlTypeMapper)
{

}

std::list<std::shared_ptr<models::Url>> UrlMapper::mapUrls(nlohmann::json json)
{
	auto urls = std::list<std::shared_ptr<models::Url>>();

	for (const auto& object: json) {
		if (!object.empty() && object.contains(JSON_KEY_URL_TYPE) && object.contains(JSON_KEY_URL)) {
			const auto& url = mapUrl(object);
			urls.emplace_back(url);
		}
	}

	return urls;
}

std::shared_ptr<models::Url> UrlMapper::mapUrl(nlohmann::json json)
{
	const auto& url = std::make_shared<models::Url>();

	url->type = urlTypeMapper->mapUrlType(json.value(JSON_KEY_URL_TYPE, std::string()));
	url->url = json.value(JSON_KEY_URL, std::string());

	return url;
}