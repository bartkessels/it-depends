#include <catch2/catch_test_macros.hpp>
#include <trompeloeil.hpp>
#include <memory>
#include <vector>
#include <QString>

#include "domain/models/Dependency.hpp"
#include "domain/models/Author.hpp"
#include "presentation/mappers/DependencyUiMapper.hpp"
#include "presentation/mappers/UrlUiMapper.hpp"

using namespace id;
using namespace id::presentation::mappers;

class UrlUiMapperMock: public presentation::contracts::IUiMapper<id::domain::models::Url, id::presentation::models::UrlUiModel>
{
	public:
		MAKE_MOCK1(map, std::vector<std::shared_ptr<presentation::models::UrlUiModel>>(const std::vector<std::shared_ptr<domain::models::Url>>&), override);
};

TEST_CASE("DepedencyUiMapper.map()")
{
	const auto& urlUiMapperMock = std::make_shared<UrlUiMapperMock>();
	const auto& sut = std::make_shared<DependencyUiMapper>(urlUiMapperMock);
	auto models = std::vector<std::shared_ptr<domain::models::Dependency>>();

	ALLOW_CALL(*urlUiMapperMock, map(trompeloeil::_)).RETURN(std::vector<std::shared_ptr<presentation::models::UrlUiModel>>());

	SECTION("maps iconName to type-app for Type::Application")
	{
		// Arrange
		const auto& expected = QString(":icons/type-app");

		const auto& model = std::make_shared<domain::models::Dependency>();
		model->type = domain::models::Type::Application;

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expected == result.front()->iconName);
	}

	SECTION("maps iconName to type-lib for Type::Library")
	{
		// Arrange
		const auto& expected = QString(":icons/type-lib");

		const auto& model = std::make_shared<domain::models::Dependency>();
		model->type = domain::models::Type::Library;

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expected == result.front()->iconName);
	}

	SECTION("maps iconName to type-unknown for Type::Unknown")
	{
		// Arrange
		const auto& expected = QString(":icons/type-unknown");

		const auto& model = std::make_shared<domain::models::Dependency>();
		model->type = domain::models::Type::Unknown;

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expected == result.front()->iconName);
	}

	SECTION("maps iconName to type-unknown for unsupported Type")
	{
		// Arrange
		const auto& expected = QString(":icons/type-unknown");

		const auto& model = std::make_shared<domain::models::Dependency>();
		model->type = static_cast<domain::models::Type>(-1);

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expected == result.front()->iconName);
	}

	SECTION("maps name to the name of the dependency")
	{
		// Arrange
		const auto& name = "ItDepends.Core";
		const auto& expected = QString::fromStdString(name);

		const auto& model = std::make_shared<domain::models::Dependency>();
		model->name = name;

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expected == result.front()->name);
	}

	SECTION("maps author to the name of the author of the dependency if author isn't a nullptr")
	{
		// Arrange
		const auto& authorName = "Vicky Fictional";
		const auto& expected = QString::fromStdString(authorName);

		const auto& author = std::make_shared<domain::models::Author>();
		const auto& model = std::make_shared<domain::models::Dependency>();
		author->name = authorName;
		model->author = author;

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expected == result.front()->author);
	}

	SECTION("maps author to to an empty string if author of the dependency is a nullptr")
	{
		// Arrange
		const auto& model = std::make_shared<domain::models::Dependency>();
		model->author = nullptr;

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(result.front()->author.isEmpty());
	}

	SECTION("maps author to to an empty string if author of the dependency isn't set")
	{
		// Arrange
		const auto& model = std::make_shared<domain::models::Dependency>();

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(result.front()->author.isEmpty());
	}

	SECTION("maps version to the version of the dependency")
	{
		// Arrange
		const auto& version = "v0.0.1-early-stage-alpha";
		const auto& expected = QString::fromStdString(version);

		const auto& model = std::make_shared<domain::models::Dependency>();
		model->version = version;

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expected == result.front()->version);
	}

	SECTION("maps description to the description of the dependency")
	{
		// Arrange
		const auto& description = "A very stable piece of software.";
		const auto& expected = QString::fromStdString(description);

		const auto& model = std::make_shared<domain::models::Dependency>();
		model->description = description;

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(expected == result.front()->description);
	}

	SECTION("calls the urlMapper for each url")
	{
		// Arrange
		const auto& model = std::make_shared<domain::models::Dependency>();
		model->urls.emplace_back(std::make_shared<domain::models::Url>());
		model->urls.emplace_back(std::make_shared<domain::models::Url>());

		// Assert
		REQUIRE_CALL(*urlUiMapperMock, map(trompeloeil::_))
			.RETURN(std::vector<std::shared_ptr<presentation::models::UrlUiModel>>());

		// Act
		models.emplace_back(model);
		sut->map(models);
	}

	SECTION("calls the urlMapper when the depedency doesn't have urls")
	{
		// Arrange
		const auto& model = std::make_shared<domain::models::Dependency>();
		model->urls.clear();

		// Assert
		REQUIRE_CALL(*urlUiMapperMock, map(trompeloeil::_))
			.RETURN(std::vector<std::shared_ptr<presentation::models::UrlUiModel>>());

		// Act
		models.emplace_back(model);
		sut->map(models);
	}

	SECTION("maps dependencies of the dependency")
	{
		// Arrange
		const auto& rootDependencyName = "Root Dependency";
		const auto& transitiveDependency1Name = "Transitive Dependency 1";
		const auto& transitiveDependency2Name = "Transitive Dependency 2";

		const auto& transitiveDependency1 = std::make_shared<domain::models::Dependency>();
		transitiveDependency1->name = transitiveDependency1Name;

		const auto& transitiveDependency2 = std::make_shared<domain::models::Dependency>();
		transitiveDependency2->name = transitiveDependency2Name;
		transitiveDependency2->dependencies.emplace_back(transitiveDependency1);

		const auto& model = std::make_shared<domain::models::Dependency>();
		model->name = rootDependencyName;
		model->dependencies.emplace_back(transitiveDependency2);

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(rootDependencyName == result.front()->name);
		REQUIRE(transitiveDependency2Name == result.front()->dependencies.front()->name);
		REQUIRE(transitiveDependency1Name == result.front()->dependencies.front()->dependencies.front()->name);
	}

	SECTION("maps dependencies to an empty list when the dependency doesn't have transitive dependencies")
	{
		// Arrange
		const auto& model = std::make_shared<domain::models::Dependency>();

		// Act
		models.emplace_back(model);
		const auto& result = sut->map(models);

		// Assert
		REQUIRE(result.front()->dependencies.empty());
	}
}