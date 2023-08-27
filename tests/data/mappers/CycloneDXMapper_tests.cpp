//#include <catch2/catch_test_macros.hpp>
//#include <trompeloeil.hpp>
//#include <memory>
//#include <string>
//
//#include "data/implementation/FileReader.hpp"
//#include "data/mappers/CycloneDXMapper.hpp"
//#include "domain/models/Dependency.hpp"
//#include "domain/models/Url.hpp"
//#include "domain/models/UrlType.hpp"
//
//using namespace id::data::mappers;
//using namespace id::domain;
//
//TEST_CASE("CycloneDXMapper.map")
//{
//	const auto& fileReader = std::make_shared<id::data::implementation::FileReader>();
//	const auto& sut = std::make_shared<CycloneDXMapper>(fileReader);
//
//	SECTION("maps urls")
//	{
//		// Arrange
//		const auto& expected = std::make_unique<models::Dependency>();
//
//
//		// Act
//		const auto& result = sut->map("./cyclonedx_sbom.json");
//
//		// Assert
//	}
//
//	SECTION("maps dependencies")
//	{
//		// Arrange
//
//		// Act
//
//		// Assert
//	}
////std::list<std::shared_ptr<models::Dependency>> map(nlohmann::json json);
////std::shared_ptr<models::Dependency> mapDependency(nlohmann::json json);
////std::list<std::shared_ptr<models::Url>> mapUrls(nlohmann::json json);
////std::shared_ptr<models::Url> mapUrl(nlohmann::json json);
//}