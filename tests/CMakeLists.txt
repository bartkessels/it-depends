cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/cyclonedx_sbom.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCEFILES
    ../src/data/factories/FileReaderFactory.cpp
    ../src/data/factories/MapperFactory.cpp
    ../src/data/implementation/FileReader.cpp
    ../src/data/mappers/CycloneDXMapper.cpp
)

set(TESTFILES
    main.cpp

    data/factories/FileReaderFactory_tests.cpp
    data/factories/MapperFactory_tests.cpp
    data/implementation/FileReader_tests.cpp
    data/mappers/CycloneDXMapper_tests.cpp
)

add_executable(id_tests ${SOURCEFILES} ${TESTFILES})
include_directories(../src)

target_link_libraries(id_tests nlohmann_json::nlohmann_json)
target_link_libraries(id_tests trompeloeil Catch2::Catch2)

enable_testing()
add_test(NAME id_tests COMMAND id_tests)
