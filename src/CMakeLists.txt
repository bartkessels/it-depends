cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if (use_installed_dependencies)
    find_package(nlohmann_json REQUIRED)
endif()

if (use_qt6)
    find_package(Qt6 COMPONENTS Widgets Core REQUIRED)
else()
    find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
endif()

set(SOURCEFILES
        main.cpp

        data/builders/CycloneDXMapperBuilder.cpp

        data/factories/BuilderFactory.cpp
        data/factories/FileReaderFactory.cpp
        data/factories/MapperFactory.cpp
        data/implementation/FileReader.cpp

        data/mappers/cyclonedx/DependencyMapper.cpp
        data/mappers/cyclonedx/HashMapper.cpp
        data/mappers/cyclonedx/LicenseMapper.cpp
        data/mappers/cyclonedx/UrlMapper.cpp
        data/mappers/cyclonedx/UrlTypeMapper.cpp
        data/mappers/CycloneDXMapper.cpp

        presentation/mappers/DependencyUiMapper.cpp
        presentation/mappers/UrlUiMapper.cpp
        presentation/widgets/DependencyListWidget/DependencyListWidget.cpp
        presentation/windows/MainWindow.cpp
        presentation/windows/MainWindowViewModel.cpp
)

add_executable(
        ${CMAKE_PROJECT_NAME}
        ${SOURCEFILES}
        ../resources/resources.qrc
)

install(TARGETS ${CMAKE_PROJECT_NAME}
        RUNTIME
        DESTINATION bin
)

target_link_libraries(${CMAKE_PROJECT_NAME} nlohmann_json::nlohmann_json)

if (use_qt6)
    target_link_libraries(${CMAKE_PROJECT_NAME} Qt::Widgets Qt::Core)
else()
    target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Widgets Qt5::Core)
endif()

if (packaging)
    include(${CMAKE_SOURCE_DIR}/packaging/CMakeLists.txt)
endif()