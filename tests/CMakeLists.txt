cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

if (generate_coverage_report)
    # TODO: Setup flags for code coverage
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -fprofile-instr-generate -fcoverage-mapping")
#    set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fprofile-instr-generate -fcoverage-mapping")
endif()

if (use_qt6)
    find_package(Qt6 COMPONENTS Core REQUIRED)
else()
    find_package(Qt5 COMPONENTS Core REQUIRED)
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/cyclonedx_sbom.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCEFILES
    ../src/data/builders/CycloneDXMapperBuilder.cpp
    ../src/data/factories/BuilderFactory.cpp
    ../src/data/factories/FileReaderFactory.cpp
    ../src/data/factories/MapperFactory.cpp
    ../src/data/implementation/FileReader.cpp

    ../src/data/mappers/cyclonedx/DependencyMapper.cpp
    ../src/data/mappers/cyclonedx/HashMapper.cpp
    ../src/data/mappers/cyclonedx/LicenseMapper.cpp
    ../src/data/mappers/cyclonedx/UrlMapper.cpp
    ../src/data/mappers/cyclonedx/UrlTypeMapper.cpp
    ../src/data/mappers/CycloneDXMapper.cpp

    ../src/presentation/mappers/DependencyUiMapper.cpp
    ../src/presentation/mappers/UrlUiMapper.cpp
    ../src/presentation/windows/MainWindowViewModel.cpp
)

set(TESTFILES
    data/builders/CycloneDXMapperBuilder_tests.cpp
    data/factories/BuilderFactory_tests.cpp
    data/factories/FileReaderFactory_tests.cpp
    data/factories/MapperFactory_tests.cpp
    data/implementation/FileReader_tests.cpp

    data/mappers/cyclonedx/DependencyMapper_tests.cpp
    data/mappers/cyclonedx/HashMapper_tests.cpp
    data/mappers/cyclonedx/LicenseMapper_tests.cpp
    data/mappers/cyclonedx/UrlMapper_tests.cpp
    data/mappers/cyclonedx/UrlTypeMapper_tests.cpp

        presentation/mappers/DependencyUiMapper_tests.cpp
    presentation/mappers/UrlUiMapper_tests.cpp
    presentation/windows/MainWindowViewModel_tests.cpp
)

add_executable(id_tests ${SOURCEFILES} ${TESTFILES})
include_directories(../src)

target_link_libraries(id_tests nlohmann_json::nlohmann_json)
target_link_libraries(id_tests trompeloeil Catch2::Catch2WithMain)

if (use_qt6)
    target_link_libraries(id_tests Qt::Core)
else()
    target_link_libraries(id_tests Qt5::Core)
endif()

enable_testing()
add_test(NAME id_tests COMMAND id_tests)
