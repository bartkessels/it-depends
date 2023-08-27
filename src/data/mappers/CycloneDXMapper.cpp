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

std::list<std::shared_ptr<models::Dependency>> CycloneDXMapper::map(std::string filePath)
{
	auto json = nlohmann::json::parse(fileReader->readFile(filePath));
	return dependencyMapper->map(json);
}
