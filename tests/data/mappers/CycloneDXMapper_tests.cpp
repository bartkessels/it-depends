#include <catch2/catch.hpp>
#include <trompeloeil.hpp>
#include <memory>
#include <string>

#include "data/contracts/IFileReader.hpp"
#include "data/mappers/CycloneDXMapper.hpp"
#include "domain/models/Dependency.hpp"
#include "domain/models/Url.hpp"
#include "domain/models/UrlType.hpp"

using namespace id::data::mappers;
using namespace id::domain;

class FileReaderMock: public IFileReader
{
	public:
	MAKE_MOCK1(readFile, std::string(const std::string&), override);
};

TEST_CASE("CycloneDXMapper.map")
{
	const auto& fileReader = std::make_shared<FileReaderMock>();
	const auto& sut = std::make_shared<CycloneDXMapper>(fileReader);

	SECTION("maps urls")
	{
		// Arrange

		// Act

		// Assert
	}

	SECTION("maps dependencies")
	{
		// Arrange

		// Act

		// Assert
	}
//std::list<std::shared_ptr<models::Dependency>> mapDependencies(nlohmann::json json);
//std::shared_ptr<models::Dependency> mapDependency(nlohmann::json json);
//std::list<std::shared_ptr<models::Url>> mapUrls(nlohmann::json json);
//std::shared_ptr<models::Url> mapUrl(nlohmann::json json);
}