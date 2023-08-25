#include <catch2/catch.hpp>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

#include "data/mappers/cyclonedx/LicenseMapper.hpp"

using namespace id::data::mappers::cyclonedx;

TEST_CASE("LicenseMapper.mapLicenses")
{
	const auto& sut = std::make_shared<LicenseMapper>();

	SECTION("maps the name and url for a single license")
	{
		// Arrange
		const auto& expectedName = "Apache-2.0";
		const auto& expectedUrl = "https://www.apache.org/licenses/LICENSE-2.0";

		const nlohmann::json& json = {
				{
						{
							"license", {
								{ "name", expectedName },
								{ "url", expectedUrl }
							}
						}
				}
		};

		// Act
		const auto& result = sut->mapLicenses(json);

		// Assert
		REQUIRE(result.front()->name == expectedName);
		REQUIRE(result.front()->url == expectedUrl);
	}

	SECTION("maps the name and url for multiple licenses")
	{
		// Arrange
		const auto& expectedNameOne = "Apache-2.0";
		const auto& expectedNameTwo = "Custom License";
		const auto& expectedUrlOne = std::string();
		const auto& expectedUrlTwo = "https://google.com";

		const nlohmann::json& json = {
				{
						{
							"license", {
								{ "id", expectedNameOne },
								{ "url", expectedUrlOne }
							}
						}
				},
				{
					{
						"license", {
							{ "name", expectedNameTwo },
							{ "url", expectedUrlTwo }
						}
					}
				}
		};

		// Act
		const auto& result = sut->mapLicenses(json);

		// Assert
		REQUIRE(result.front()->name == expectedNameOne);
		REQUIRE(result.front()->url == expectedUrlOne);

		REQUIRE(result.back()->name == expectedNameTwo);
		REQUIRE(result.back()->url == expectedUrlTwo);
	}

	SECTION("maps the name of the license to the id if it's set")
	{
		// Arrange
		const auto& expectedName = "Apache-2.0";

		const nlohmann::json& json = {
				{
						{
							"license", {
								{ "id", expectedName },
								{ "url", "https://www.apache.org/licenses/LICENSE-2.0" }
							}
						}
				}
		};

		// Act
		const auto& result = sut->mapLicenses(json);

		// Assert
		REQUIRE(result.front()->name == expectedName);
	}

	SECTION("maps the name of the license to the name if the id is not available in the json object")
	{
		// Arrange
		const auto& expectedName = "Apache-2.0";

		const nlohmann::json& json = {
				{
						{
							"license", {
								{ "name", expectedName },
								{ "url", "https://www.apache.org/licenses/LICENSE-2.0" }
							}
						}
				}
		};

		// Act
		const auto& result = sut->mapLicenses(json);

		// Assert
		REQUIRE(result.front()->name == expectedName);
	}

	SECTION("maps the name of the license to an empty string if both the name and the id aren't available in the json object")
	{
		// Arrange
		const auto& expectedName = std::string();

		const nlohmann::json& json = {
				{
						{
							"license", {
								{ "url", "https://www.apache.org/licenses/LICENSE-2.0" }
							}
						}
				}
		};

		// Act
		const auto& result = sut->mapLicenses(json);

		// Assert
		REQUIRE(result.front()->name == expectedName);
	}

	SECTION("maps the url to an empty string if it's not available in the json object")
	{
		// Arrange
		const auto& expectedUrl = std::string();

		const nlohmann::json& json = {
				{
						{
							"license", {
								{ "id", "Apache-2.0" }
							}
						}
				}
		};

		// Act
		const auto& result = sut->mapLicenses(json);

		// Assert
		REQUIRE(result.front()->url == expectedUrl);
	}

	SECTION("returns an empty list when the license is an empty object")
	{
		// Arrange
		const auto& json = nlohmann::json::parse(R"([{"license": {}}])");

		// Act
		const auto& result = sut->mapLicenses(json);

		// Assert
		REQUIRE(result.empty());
	}

	SECTION("returns an empty list when no license object is available")
	{
		// Arrange
		const auto& json = nlohmann::json::parse("[{}]");

		// Act
		const auto& result = sut->mapLicenses(json);

		// Assert
		REQUIRE(result.empty());
	}

	SECTION("returns an empty list when an empty json object is given")
	{
		// Arrange
		const auto& json = nlohmann::json::parse("{}");

		// Act
		const auto& result = sut->mapLicenses(json);

		// Assert
		REQUIRE(result.empty());
	}

	SECTION("returns an empty list when an empty json array is given")
	{
		// Arrange
		const auto& json = nlohmann::json::parse("[]");

		// Act
		const auto& result = sut->mapLicenses(json);

		// Assert
		REQUIRE(result.empty());
	}
}