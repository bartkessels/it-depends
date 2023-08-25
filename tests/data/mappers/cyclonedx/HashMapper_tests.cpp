#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

#include "data/mappers/cyclonedx/HashMapper.hpp"

using namespace id::data::mappers::cyclonedx;

TEST_CASE("HashMapper.mapHashes")
{
	const auto& sut = std::make_shared<HashMapper>();

	SECTION("maps the algorithm and value for a single hash")
	{
		// Arrange
		const auto& expectedAlgorithm = "MD5";
		const auto& expectedHashValue = "01b1a8cff910fdb9328cef5c437ff2f9";

		const nlohmann::json& json = {
				{
						{ "alg", expectedAlgorithm },
						{ "content", expectedHashValue }
				}
		};

		// Act
		const auto& result = sut->mapHashes(json);

		// Assert
		REQUIRE(result.front()->algorithm == expectedAlgorithm);
		REQUIRE(result.front()->value == expectedHashValue);
	}

	SECTION("maps the algorithm and value for a multiple hashes")
	{
		// Arrange
		const auto& expectedAlgorithmOne = "MD5";
		const auto& expectedAlgorithmTwo = "SHA-256";
		const auto& expectedHashValueOne = "01b1a8cff910fdb9328cef5c437ff2f9";
		const auto& expectedHashValueTwo = "2fa0ab71b154da29ac134097bc6bbacd90987dd4c4005516159e6494d1d52ea2";

		const nlohmann::json& json = {
				{
						{ "alg", expectedAlgorithmOne },
						{ "content", expectedHashValueOne }
				},
				{
						{ "alg", expectedAlgorithmTwo },
						{ "content", expectedHashValueTwo }
				}
		};

		// Act
		const auto& result = sut->mapHashes(json);

		// Assert
		REQUIRE(result.front()->algorithm == expectedAlgorithmOne);
		REQUIRE(result.front()->value == expectedHashValueOne);

		REQUIRE(result.back()->algorithm == expectedAlgorithmTwo);
		REQUIRE(result.back()->value == expectedHashValueTwo);
	}

	SECTION("maps the algorithm to an empty string when it's not available in the json object")
	{
		// Arrange
		const nlohmann::json& json = {
				{
						   { "content", "01b1a8cff910fdb9328cef5c437ff2f9" }
				}
		};

		// Act
		const auto& result = sut->mapHashes(json);

		// Assert
		REQUIRE(result.front()->algorithm == std::string());
	}

	SECTION("maps the value to an empty string when it's not available in the json object")
	{
		// Arrange
		const nlohmann::json& json = {
				{
						   { "alg", "MD5" }
				}
		};

		// Act
		const auto& result = sut->mapHashes(json);

		// Assert
		REQUIRE(result.front()->value == std::string());
	}

	SECTION("returns an empty list when the hash is an empty object")
	{
		// Arrange
		const auto& json = nlohmann::json::parse("[{}]");

		// Act
		const auto& result = sut->mapHashes(json);

		// Assert
		REQUIRE(result.empty());
	}

	SECTION("returns a list with one object if one of the two is an empty object")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"(
			[
				{},
				{
					"alg": "MD5",
					"content": "01b1a8cff910fdb9328cef5c437ff2f9"
				}
			]
		)");

		// Act
		const auto& result = sut->mapHashes(json);

		// Assert
		REQUIRE(result.size() == 1);
	}

	SECTION("returns an empty list when an empty json object is given")
	{
		// Arrange
		const auto& json = nlohmann::json::parse("{}");

		// Act
		const auto& result = sut->mapHashes(json);

		// Assert
		REQUIRE(result.empty());
	}

	SECTION("returns an empty list when an empty json array is given")
	{
		// Arrange
		const auto& json = nlohmann::json::parse("[]");

		// Act
		const auto& result = sut->mapHashes(json);

		// Assert
		REQUIRE(result.empty());
	}
}