#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "data/factories/FileReaderFactory.hpp"
#include "data/implementation/FileReader.hpp"
#include "domain/SbomType.hpp"

using namespace id::data::factories;
using namespace id::data::implementation;

TEST_CASE("FileReaderFactory.getFileReader")
{
	const auto& sut = std::make_shared<FileReaderFactory>();

	SECTION("returns an instance of FileReader")
	{
		// Arrange
		// Act
		const auto& result = sut->getFileReader();

		// Assert
		REQUIRE(std::dynamic_pointer_cast<FileReader>(result));
	}
}