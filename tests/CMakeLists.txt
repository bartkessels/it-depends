cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(SOURCEFILES)

set(TESTFILES
    main.cpp

    temp_tst.cpp
)

add_executable(id_tests ${SOURCEFILES} ${TESTFILES})
include_directories(../src)

target_link_libraries(id_tests nlohmann_json::nlohmann_json)
target_link_libraries(id_tests trompeloeil Catch2::Catch2)

enable_testing()
add_test(NAME id_tests COMMAND id_tests)
