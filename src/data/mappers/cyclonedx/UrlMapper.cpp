#include "data/mappers/cyclonedx/UrlMapper.hpp"

using namespace id::data::mappers::cyclonedx;

UrlMapper::UrlMapper(std::shared_ptr<UrlTypeMapper> urlTypeMapper):
	urlTypeMapper(std::move(urlTypeMapper))
{

}

auto UrlMapper::map(const nlohmann::json& json) -> std::list<std::shared_ptr<models::Url>>
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

auto UrlMapper::mapUrl(const nlohmann::json& json) -> std::shared_ptr<models::Url>
{
	const auto& url = std::make_shared<models::Url>();

	url->type = urlTypeMapper->map(json.value(JSON_KEY_URL_TYPE, std::string()));
	url->url = json.value(JSON_KEY_URL, std::string());

	return url;
}