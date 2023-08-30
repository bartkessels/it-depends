#include "data/mappers/CycloneDXMapper.hpp"

using namespace id::data::mappers;
using namespace id::domain;

CycloneDXMapper::CycloneDXMapper(
	std::shared_ptr<contracts::IFileReader> fileReader,
	std::shared_ptr<cyclonedx::DependencyMapper> dependencyMapper
):
	fileReader(fileReader),
	dependencyMapper(dependencyMapper)
{

}

auto CycloneDXMapper::map(const std::string& filePath) -> std::list<std::shared_ptr<models::Dependency>>
{
	auto json = nlohmann::json::parse(fileReader->readFile(filePath));
	return dependencyMapper->map(json);
}
