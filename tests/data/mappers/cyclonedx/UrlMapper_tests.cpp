#include <catch2/catch_test_macros.hpp>
#include <trompeloeil.hpp>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

#include "data/mappers/cyclonedx/UrlMapper.hpp"
#include "data/mappers/cyclonedx/UrlTypeMapper.hpp"
#include "domain/models/UrlType.hpp"

using namespace id::data::mappers::cyclonedx;
using namespace id::domain;

class UrlTypeMapperMock: public UrlTypeMapper
{
	public:
		MAKE_MOCK1(map, models::UrlType(const std::string&));
};

TEST_CASE("UrlMapper.map")
{
	const auto& urlTypeMapperMock = std::make_shared<UrlTypeMapperMock>();
	const auto& sut = std::make_shared<UrlMapper>(urlTypeMapperMock);

	SECTION("maps the type and url for a single url")
	{
		// Arrange
		const auto& expectedType = models::UrlType::VCS;
		const auto& expectedUrl = "https://github.com/bcgit/bc-java";

		ALLOW_CALL(*urlTypeMapperMock, map(trompeloeil::_)).RETURN(expectedType);

		const nlohmann::json& json = {
				{
						{ "type", "vcs" },
						{ "url", expectedUrl }
				}
		};

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.front()->type == expectedType);
		REQUIRE(result.front()->url == expectedUrl);
	}

	SECTION("maps the type and url for a multiple url")
	{
		// Arrange
		const auto& expectedTypeOne = models::UrlType::VCS;
		const auto& expectedTypeTwo = models::UrlType::IssueTracker;
		const auto& expectedUrlOne = "https://github.com/bcgit/bc-java";
		const auto& expectedUrlTwo = "https://github.com/bcgit/bc-java/issues";

		trompeloeil::sequence seq;
		ALLOW_CALL(*urlTypeMapperMock, map(trompeloeil::_))
			.RETURN(expectedTypeOne)
			.IN_SEQUENCE(seq);

		ALLOW_CALL(*urlTypeMapperMock, map(trompeloeil::_))
				.RETURN(expectedTypeTwo)
				.IN_SEQUENCE(seq);

		const nlohmann::json& json = {
				{
						{ "type", "vcs" },
						{ "url", expectedUrlOne }
				},
				{
						{ "type", "issue-tracker" },
						{ "url", expectedUrlTwo }
				}
		};

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.front()->type == expectedTypeOne);
		REQUIRE(result.front()->url == expectedUrlOne);

		REQUIRE(result.back()->type == expectedTypeTwo);
		REQUIRE(result.back()->url == expectedUrlTwo);
	}

	SECTION("returns an empty list when the type is not available in the json object")
	{
		// Arrange
		const nlohmann::json& json = {
				{
						{ "url", "https://github.com/bcgit/bc-java" }
				}
		};

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.empty());
	}

	SECTION("returns an empty list when the url is not available in the json object")
	{
		// Arrange
		const nlohmann::json& json = {
				{
						{ "type", "vcs" }
				}
		};

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.empty());
	}

	SECTION("returns an ampty list when the url object is an empty object")
	{
		// Arrange
		const auto& json = nlohmann::json::parse("[{}]");

		// Act
		const auto& result = sut->map(json);

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
					"type": "vcs",
					"url": "https://github.com/bcgit/bc-java"
				}
			]
		)");

		ALLOW_CALL(*urlTypeMapperMock, map(trompeloeil::_)).RETURN(models::UrlType::VCS);

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.size() == 1);
	}

	SECTION("returns an empty list when an empty json object is given")
	{
		// Arrange
		const auto& json = nlohmann::json::parse("{}");

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.empty());
	}

	SECTION("returns an empty list when an json array is given")
	{
		// Arrange
		const auto& json = nlohmann::json::parse("[]");

		// Act
		const auto& result = sut->map(json);

		// Assert
		REQUIRE(result.empty());
	}
}