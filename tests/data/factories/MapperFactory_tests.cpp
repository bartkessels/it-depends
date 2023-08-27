#include <catch2/catch_test_macros.hpp>
#include <trompeloeil.hpp>
#include <memory>
#include <string>

#include "data/contracts/IBuilderFactory.hpp"
#include "data/contracts/IFileReader.hpp"
#include "data/contracts/IFileReaderFactory.hpp"
#include "data/factories/MapperFactory.hpp"
#include "domain/SbomType.hpp"

using namespace id::data::contracts;
using namespace id::data::factories;
using namespace id::domain;

class FileReaderMock: public IFileReader
{
	public:
		MAKE_MOCK1(readFile, std::string(const std::string&), override);
};

class FileReaderFactoryMock: public IFileReaderFactory
{
	public:
		MAKE_MOCK0(getFileReader, std::shared_ptr<IFileReader>(), override);
};

class BuilderFactoryMock: public IBuilderFactory
{
	public:
		MAKE_MOCK1(build, (std::shared_ptr<IMapperBuilder>(SbomType)), override);
};

class MapperBuilderMock: public IMapperBuilder
{
	public:
		MAKE_MOCK1(build, std::shared_ptr<IMapper>(std::shared_ptr<IFileReader>), override);
};

class MapperMock: public IMapper
{
	public:
		MAKE_MOCK1(map, std::list<std::shared_ptr<models::Dependency>>(std::string), override);
};

TEST_CASE("MapperFactory.getMapper")
{
	const auto& fileReaderFactoryMock = std::make_shared<FileReaderFactoryMock>();
	const auto& fileReaderMock = std::make_shared<FileReaderMock>();
	const auto& builderFactoryMock = std::make_shared<BuilderFactoryMock>();
	const auto& mapperBuilderMock = std::make_shared<MapperBuilderMock>();
	const auto& mapperMock = std::make_shared<MapperMock>();

	const auto& sut = std::make_shared<MapperFactory>(fileReaderFactoryMock, builderFactoryMock);

	ALLOW_CALL(*fileReaderFactoryMock, getFileReader()).RETURN(fileReaderMock);
	ALLOW_CALL(*builderFactoryMock, build(trompeloeil::_)).RETURN(mapperBuilderMock);
	ALLOW_CALL(*mapperBuilderMock, build(trompeloeil::_)).RETURN(mapperMock);

	SECTION("calls getFileReader on the FileReaderFactory")
	{
		// Arrange
		const auto& type = id::domain::SbomType::CycloneDX;

		// Assert
		REQUIRE_CALL(*fileReaderFactoryMock, getFileReader()).RETURN(fileReaderMock);

		// Act
		sut->getMapper(type);
	}

	SECTION("calls build with the correct SBOM type on the BuilderFactory")
	{
		// Arrange
		const auto& type = id::domain::SbomType::CycloneDX;

		// Assert
		REQUIRE_CALL(*builderFactoryMock, build(type)).RETURN(mapperBuilderMock);

		// Act
		sut->getMapper(type);
	}

	SECTION("calls build on the builder with the generated file reader")
	{
		// Arrange
		const auto& type = id::domain::SbomType::CycloneDX;

		// Assert
		REQUIRE_CALL(*mapperBuilderMock, build(fileReaderMock)).RETURN(mapperMock);

		// Act
		sut->getMapper(type);
	}
}