#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "data/mappers/cyclonedx/UrlTypeMapper.hpp"
#include "domain/models/UrlType.hpp"

using namespace id::data::mappers::cyclonedx;
using namespace id::domain;

TEST_CASE("UrlTypeMapper.mapUrlType")
{
	const auto& sut = std::shared_ptr<UrlTypeMapper>();

	SECTION("returns Website when a nullptr is given")
	{
		std::string type;
		const auto& expected = models::UrlType::Website;

		// Act
		const auto& result = sut->mapUrlType(type);

		// Assert
		REQUIRE(result == expected);
	}

	SECTION("returns Website when an empty string is given")
	{
		// Arrange
		const auto& type = std::string();
		const auto& expected = models::UrlType::Website;

		// Act
		const auto& result = sut->mapUrlType(type);

		// Assert
		REQUIRE(result == expected);
	}

	SECTION("returns Website when an unknown type is given")
	{
		// Arrange
		const auto& type = "unknown";
		const auto& expected = models::UrlType::Website;

		// Act
		const auto& result = sut->mapUrlType(type);

		// Assert
		REQUIRE(result == expected);
	}

	SECTION("returns IssueTracker for the issue-tracker type")
	{
		// Arrange
		const auto& type = "issue-tracker";
		const auto& expected = models::UrlType::IssueTracker;

		// Act
		const auto& result = sut->mapUrlType(type);

		// Assert
		REQUIRE(result == expected);
	}

	SECTION("returns VCS for the vcs type")
	{
		// Arrange
		const auto& type = "vcs";
		const auto& expected = models::UrlType::VCS;

		// Act
		const auto& result = sut->mapUrlType(type);

		// Assert
		REQUIRE(result == expected);
	}
}