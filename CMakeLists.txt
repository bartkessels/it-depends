cmake_minimum_required(VERSION 3.26)

project(ItDepends
        VERSION 1.0.0
        DESCRIPTION "Get insights in your software dependencies based on a generated SBOM"
        HOMEPAGE_URL "https://github.com/bartkessels/it-depends"
)

# Optional arguments for compiling It Depends
OPTION(use_installed_dependencies "Use the installed versions of the dependencies for It Depends instead of fetching them using FetchContent" false)
OPTION(packaging "Package It Depends for all supported platforms" false)
OPTION(use_qt6 "Use Qt6 instead of Qt5" true)

# General project setup
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build)

add_subdirectory(src)

if (NOT use_installed_dependencies)
    add_subdirectory(third_party)
endif()

if (packaging)
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    include(CPack)
else()
    add_subdirectory(tests)
endif()