//#include <catch2/catch.hpp>
//#include <trompeloeil.hpp>
//#include <memory>
//#include <string>
//
//#include "data/contracts/IBuilderFactory.hpp"
//#include "data/contracts/IFileReader.hpp"
//#include "data/contracts/IFileReaderFactory.hpp"
//#include "data/factories/MapperFactory.hpp"
//#include "data/mappers/CycloneDXMapper.hpp"
//#include "domain/SbomType.hpp"
//
//using namespace id::data::contracts;
//using namespace id::data::factories;
//using namespace id::data::mappers;
//using namespace id::domain;
//
//class FileReaderMock: public IFileReader
//{
//	public:
//		MAKE_MOCK1(readFile, std::string(const std::string&), override);
//};
//
//class FileReaderFactoryMock: public IFileReaderFactory
//{
//	public:
//		MAKE_MOCK0(getFileReader, std::shared_ptr<IFileReader>(), override);
//};
//
//class BuilderFactoryMock: public IBuilderFactory
//{
//	public:
//		MAKE_MOCK1(createBuilder, (std::shared_ptr<IMapperBuilder>(SbomType)), override);
//};
//
//TEST_CASE("MapperFactory.getMapper")
//{
//	const auto& fileReaderFactoryMock = std::make_shared<FileReaderFactoryMock>();
//	const auto& fileReaderMock = std::make_shared<FileReaderMock>();
//	const auto& builderFactoryMock = std::make_shared<BuilderFactoryMock>();
//	const auto& sut = std::make_shared<MapperFactory>(fileReaderFactoryMock, builderFactoryMock);
//
//	ALLOW_CALL(*fileReaderFactoryMock, getFileReader()).RETURN(fileReaderMock);
//
//	SECTION("returns the CycloneDX mapper for the SbomType::CycloneDX")
//	{
//		// Arrange
//		const auto& type = id::domain::SbomType::CycloneDX;
//
//		// Act
//		const auto& result = sut->getMapper(type);
//
//		// Assert
//		REQUIRE(std::dynamic_pointer_cast<CycloneDXMapper>(result));
//	}
//
//	SECTION("throws an exception when passing a non-existing parser type")
//	{
//		// Arrange
//		const auto& type = static_cast<id::domain::SbomType>(-1);
//
//		// Act & Assert
//		REQUIRE_THROWS(
//			sut->getMapper(type)
//		);
//	}
//}