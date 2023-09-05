#include <catch2/catch_test_macros.hpp>
#include <trompeloeil.hpp>
#include <exception>
#include <string>
#include <memory>
#include <vector>

#include "data/contracts/IMapperFactory.hpp"
#include "domain/models/Dependency.hpp"
#include "presentation/contracts/IUiMapper.hpp"
#include "presentation/models/DependencyUiModel.hpp"
#include "presentation/states/MainWindowState.hpp"
#include "presentation/windows/IMainWindow.hpp"
#include "presentation/windows/MainWindowViewModel.hpp"

using namespace id;
using namespace id::presentation;

class MainWindowMock: public windows::IMainWindow
{
	public:
		MAKE_MOCK1(setViewModel, void(const std::shared_ptr<windows::IMainWindowViewModel>&), override);
		MAKE_MOCK1(updateState, void(const std::shared_ptr<states::MainWindowState>&), override);
};

class MapperMock: public data::contracts::IMapper
{
	public:
		MAKE_MOCK1(map, std::vector<std::shared_ptr<domain::models::Dependency>>(const std::string&), override);
};

class MapperFactoryMock: public data::contracts::IMapperFactory
{
	public:
		MAKE_MOCK1(getMapper, std::shared_ptr<data::contracts::IMapper>(domain::SbomType), override);
};

class UiMapperMock: public presentation::contracts::IUiMapper<domain::models::Dependency, presentation::models::DependencyUiModel>
{
	public:
		MAKE_MOCK1(map, std::vector<std::shared_ptr<presentation::models::DependencyUiModel>>(const std::vector<std::shared_ptr<domain::models::Dependency>>&), override);
};

TEST_CASE("MainWindowViewModel.ctor")
{
	const auto& windowMock = std::make_shared<MainWindowMock>();
	const auto& mapperMock = std::make_shared<MapperMock>();
	const auto& mapperFactoryMock = std::make_shared<MapperFactoryMock>();
	const auto& uiMapperMock = std::make_shared<UiMapperMock>();

	SECTION("sets the default state to State::Empty")
	{
		// Assert
		REQUIRE_CALL(*windowMock, updateState(trompeloeil::_))
			.WITH(std::dynamic_pointer_cast<states::EmptyState>(_1) != nullptr);

		// Act
		std::make_shared<windows::MainWindowViewModel>(
				windowMock,
				mapperFactoryMock,
				uiMapperMock
		);
	}
}

TEST_CASE("MainWindowViewModel.loadSBOM()")
{
	const auto& windowMock = std::make_shared<MainWindowMock>();
	const auto& mapperMock = std::make_shared<MapperMock>();
	const auto& mapperFactoryMock = std::make_shared<MapperFactoryMock>();
	const auto& uiMapperMock = std::make_shared<UiMapperMock>();

	ALLOW_CALL(*windowMock, setViewModel(trompeloeil::_));
	ALLOW_CALL(*windowMock, updateState(trompeloeil::_));
	ALLOW_CALL(*mapperMock, map(trompeloeil::_)).RETURN(std::vector<std::shared_ptr<domain::models::Dependency>>());
	ALLOW_CALL(*mapperFactoryMock, getMapper(trompeloeil::_)).RETURN(mapperMock);
	ALLOW_CALL(*uiMapperMock, map(trompeloeil::_)).RETURN(std::vector<std::shared_ptr<presentation::models::DependencyUiModel>>());

	const auto& sut = std::make_shared<windows::MainWindowViewModel>(
		windowMock,
		mapperFactoryMock,
		uiMapperMock
	);

	SECTION("should update the state to loading before anything happens")
	{
		// Arrange
		const auto& type = domain::SbomType::CycloneDX;
		const auto& fileLocation = "./sbom.json";

		// Assert
		REQUIRE_CALL(*windowMock, updateState(trompeloeil::_))
			.WITH(std::dynamic_pointer_cast<states::LoadingState>(_1) != nullptr);

		// Act
		sut->loadSBOM(type, fileLocation);
		sut->loadingThread.join();
	}

	SECTION("should call getMapper on the IMapperFactory with the expected type")
	{
		// Arrange
		const auto& expectedType = domain::SbomType::CycloneDX;
		const auto& fileLocation = "./sbom.json";

		// Assert
		REQUIRE_CALL(*mapperFactoryMock, getMapper(trompeloeil::_))
			.WITH(domain::SbomType(_1) == expectedType)
			.RETURN(mapperMock);

		// Act
		sut->loadSBOM(expectedType, fileLocation);
		sut->loadingThread.join();
	}

	SECTION("should call map on the IMapper with the expected file location")
	{
		// Arrange
		const auto& type = domain::SbomType::CycloneDX;
		const auto& expectedFileLocation = "./sbom.json";

		// Assert
		REQUIRE_CALL(*mapperMock, map(trompeloeil::_))
			.WITH(std::string(_1) == expectedFileLocation)
			.RETURN(std::vector<std::shared_ptr<domain::models::Dependency>>());

		// Act
		sut->loadSBOM(type, expectedFileLocation);
		sut->loadingThread.join();
	}

	SECTION("should call map on the IUiMapper")
	{
		// Arrange
		const auto& type = domain::SbomType::CycloneDX;
		const auto& fileLocation = "./sbom.json";

		// Assert
		REQUIRE_CALL(*uiMapperMock, map(trompeloeil::_))
			.RETURN(std::vector<std::shared_ptr<presentation::models::DependencyUiModel>>());

		// Act
		sut->loadSBOM(type, fileLocation);
		sut->loadingThread.join();
	}

	SECTION("should update the state to success when the mapping succeeded")
	{
		// Arrange
		const auto& type = domain::SbomType::CycloneDX;
		const auto& fileLocation = "./sbom.json";

		// Assert
		REQUIRE_CALL(*windowMock, updateState(trompeloeil::_))
			.WITH(std::dynamic_pointer_cast<states::SuccessState>(_1) != nullptr);

		// Act
		sut->loadSBOM(type, fileLocation);
		sut->loadingThread.join();

	}

	SECTION("should update the state to error when the IMapperFactory throws an exception")
	{
		// Arrange
		const auto& type = domain::SbomType::CycloneDX;
		const auto& fileLocation = "./sbom.json";

		ALLOW_CALL(*mapperFactoryMock, getMapper(trompeloeil::_))
			.THROW(std::exception());

		// Assert
		REQUIRE_CALL(*windowMock, updateState(trompeloeil::_))
			.WITH(std::dynamic_pointer_cast<states::LoadingState>(_1) != nullptr);

		// Act
		sut->loadSBOM(type, fileLocation);
		sut->loadingThread.join();

	}

	SECTION("should update the state to error when the IMapper throws an exception")
	{
		// Arrange
		const auto& type = domain::SbomType::CycloneDX;
		const auto& fileLocation = "./sbom.json";

		ALLOW_CALL(*mapperMock, map(trompeloeil::_))
		.THROW(std::exception());

		// Assert
		REQUIRE_CALL(*windowMock, updateState(trompeloeil::_))
			.WITH(std::dynamic_pointer_cast<states::LoadingState>(_1) != nullptr);

		// Act
		sut->loadSBOM(type, fileLocation);
		sut->loadingThread.join();
	}

	SECTION("should update the state to error when the IUiMapper throws an exception")
	{
		// Arrange
		const auto& type = domain::SbomType::CycloneDX;
		const auto& fileLocation = "./sbom.json";

		ALLOW_CALL(*uiMapperMock, map(trompeloeil::_))
			.THROW(std::exception());

		// Assert
		REQUIRE_CALL(*windowMock, updateState(trompeloeil::_))
			.WITH(std::dynamic_pointer_cast<states::ErrorState>(_1) != nullptr);

		// Act
		sut->loadSBOM(type, fileLocation);
		sut->loadingThread.join();
	}
}