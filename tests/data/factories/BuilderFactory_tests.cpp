#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "data/builders/CycloneDXMapperBuilder.hpp"
#include "data/exceptions/UnsupportedSBOMTypeException.hpp"
#include "data/factories/BuilderFactory.hpp"
#include "domain/SbomType.hpp"

using namespace id::data::builders;
using namespace id::data::exceptions;
using namespace id::data::factories;
using namespace id::domain;

TEST_CASE("BuilderFactory.build")
{
	const auto& sut = std::make_shared<BuilderFactory>();

	SECTION("returns an instance of CycloneDXMapperBuilder for the CycloneDX SBOM type")
	{
		// Arrange
		const auto& type = SbomType::CycloneDX;

		// Act
		const auto& result = sut->build(type);

		// Assert
		REQUIRE(std::dynamic_pointer_cast<CycloneDXMapperBuilder>(result));
	}

	SECTION("throws an exception for an unsupported SBOM type")
	{
		// Arrange
		const auto& type = static_cast<id::domain::SbomType>(-1);

		// Act & Assert
		REQUIRE_THROWS_AS(
			sut->build(type),
			UnsupportedSBOMTypeException
		);
	}
}