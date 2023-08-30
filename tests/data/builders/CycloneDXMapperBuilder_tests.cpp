#include <catch2/catch_test_macros.hpp>
#include <trompeloeil.hpp>
#include <memory>
#include <string>

#include "data/builders/CycloneDXMapperBuilder.hpp"
#include "data/contracts/IFileReader.hpp"
#include "data/mappers/CycloneDXMapper.hpp"

using namespace id::data::builders;
using namespace id::data::mappers;

class FileReaderMock: public id::data::contracts::IFileReader
{
	public:
		MAKE_MOCK1(readFile, std::string(const std::string&), override);
};

TEST_CASE("CycloneDXMapperBuilder.builder")
{
	const auto& fileReaderMock = std::make_shared<FileReaderMock>();
	const auto& sut = std::make_shared<CycloneDXMapperBuilder>();

	ALLOW_CALL(*fileReaderMock, readFile(trompeloeil::_)).RETURN(std::string());

	SECTION("creates and instance of CycloneDXMapper")
	{
		// Act
		const auto& result = sut->build(fileReaderMock);

		// Assert
		REQUIRE(std::dynamic_pointer_cast<CycloneDXMapper>(result));
	}
}