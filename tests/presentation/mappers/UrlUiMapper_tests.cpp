#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <QString>

#include "domain/models/Url.hpp"
#include "domain/models/UrlType.hpp"
#include "presentation/mappers/UrlUiMapper.hpp"

using namespace id;
using namespace id::presentation::mappers;

TEST_CASE("UrlUiMapper.map()")
{
	const auto& sut = std::make_unique<UrlUiMapper>();
	auto models = std::vector<std::shared_ptr<domain::models::Url>>();

	SECTION("maps the name to Issue Tracker for Type::IssueTracker")
	{
		// Arrange
		const auto& expectedName = QString("Issue tracker");

		const auto& model = std::make_shared<domain::models::Url>();
		model->type = domain::models::UrlType::IssueTracker;
		model->url = "https://github.com/bartkessels/it-depends";

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expectedName == result.front()->name);
	}

	SECTION("maps the name to Website for Type::Website")
	{
		// Arrange
		const auto& expectedName = QString("Website");

		const auto& model = std::make_shared<domain::models::Url>();
		model->type = domain::models::UrlType::Website;
		model->url = "https://github.com/bartkessels/it-depends";

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expectedName == result.front()->name);
	}

	SECTION("maps the name to Repository for Type::VCS")
	{
		// Arrange
		const auto& expectedName = QString("Repository");

		const auto& model = std::make_shared<domain::models::Url>();
		model->type = domain::models::UrlType::VCS;
		model->url = "https://github.com/bartkessels/it-depends";

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expectedName == result.front()->name);
	}

	SECTION("throws an exception for an unsupported type")
	{
		// Arrange
		const auto& unsupportedType = static_cast<domain::models::UrlType>(-1);

		const auto& model = std::make_shared<domain::models::Url>();
		model->type = unsupportedType;
		model->url = "https://github.com/bartkessels/it-depends";

		// Act & Assert
		models.emplace_back(model);
		
		REQUIRE_THROWS(
			sut->map(models)
		);
	}

	SECTION("maps the uri to the url of the model")
	{
		// Arrange
		const auto& expectedUri = QString("https://github.com/bartkessels/it-depends");

		const auto& model = std::make_shared<domain::models::Url>();
		model->type = domain::models::UrlType::VCS;
		model->url = "https://github.com/bartkessels/it-depends";

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expectedUri == result.front()->uri);
	}

	SECTION("maps the uri to an empty string if the model has no url")
	{
		// Arrange
		const auto& model = std::make_shared<domain::models::Url>();
		model->type = domain::models::UrlType::VCS;

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(result.front()->uri.isEmpty());
	}

	SECTION("maps the uri to an empty string if the model url is empty")
	{
		// Arrange
		const auto& model = std::make_shared<domain::models::Url>();
		model->type = domain::models::UrlType::VCS;
		model->url = std::string();

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(result.front()->uri.isEmpty());
	}
}