#include <catch2/catch.hpp>
#include <memory>
#include <string>
#include <iomanip>

#include "data/exceptions/EmptyFileException.hpp"
#include "data/exceptions/FileNotFoundException.hpp"
#include "data/implementation/FileReader.hpp"

using namespace id::data::implementation;
using namespace id::data;

void writeFile(const std::string& fileName, const std::string& contents)
{
	std::ofstream output(fileName);
	output << contents;
	output.close();
}

TEST_CASE("FileReader.readFile")
{
	const auto& sut = std::make_shared<FileReader>();

	SECTION("returns the contents from the file")
	{
		// Arrange
		const auto& fileName = "./test_file.txt";
		const auto& expected = "contents";

		writeFile(fileName, expected);

		// Act
		const auto& result = sut->readFile(fileName);

		// Assert
		REQUIRE(result == expected);

		// Teardown
		std::remove(fileName);
	}

	SECTION("should throw an FileNotFoundException when the file does not exist")
	{
		// Arrange
		const auto& fileName = "does-not-exist.txt";
		std::remove(fileName);

		// Act & Assert
		REQUIRE_THROWS_AS(
			sut->readFile(fileName), exceptions::FileNotFoundException
		);
	}

	SECTION("should throw an EmptyFileException when the file is empty")
	{
		// Arrange
		const auto& fileName = "empty-file.txt";
		const auto& contents = "";

		writeFile(fileName, contents);

		// Act & Assert
		REQUIRE_THROWS_AS(
			sut->readFile(fileName), exceptions::EmptyFileException
		);

		// Teardown
		std::remove(fileName);
	}
}