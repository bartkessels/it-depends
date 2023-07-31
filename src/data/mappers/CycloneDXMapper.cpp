#include "data/mappers/CycloneDXMapper.hpp"

using namespace id::data::mappers;
using namespace id::domain;

CycloneDXMapper::CycloneDXMapper(std::shared_ptr<contracts::IFileReader> fileReader):
	fileReader(fileReader)
{

}

std::list<std::shared_ptr<models::Dependency>> CycloneDXMapper::map(std::string filePath)
{
	auto json = nlohmann::json::parse(fileReader->readFile(filePath));
	return mapDependencies(json);
}

std::list<std::shared_ptr<models::Dependency>> CycloneDXMapper::mapDependencies(nlohmann::json json)
{
	auto dependencies = std::list<std::shared_ptr<models::Dependency>>();

	for (auto object : json["components"]) {
		const auto& dependency = mapDependency(object);
		dependencies.emplace_back(dependency);
	}

	return dependencies;
}

std::shared_ptr<models::Dependency> CycloneDXMapper::mapDependency(nlohmann::json json)
{
	const auto& dependency = std::make_shared<models::Dependency>();

	dependency->id = json["bom-ref"].get<std::string>();
	dependency->name = json["name"].get<std::string>();
	dependency->version = json["version"].get<std::string>();
	dependency->urls = mapUrls(json["externalReferences"]);

	return dependency;
}

std::list<std::shared_ptr<models::Url>> CycloneDXMapper::mapUrls(nlohmann::json json)
{
	auto urls = std::list<std::shared_ptr<models::Url>>();

	for (auto object : json) {
		const auto& url = mapUrl(object);
		urls.emplace_back(url);
	}

	return urls;
}

std::shared_ptr<models::Url> CycloneDXMapper::mapUrl(nlohmann::json json)
{
	const auto& url = std::make_shared<models::Url>();
	const auto& jsonUrlType = json["type"].get<std::string>();
	url->url = json["url"].get<std::string>();

	if (jsonUrlType == "issue-tracker") {
		url->type = models::UrlType::IssueTracker;
	} else {
		url->type = models::UrlType::Website;
	}

	return url;
}