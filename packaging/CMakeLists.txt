cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

if (APPLE)
    add_subdirectory(macos)
elseif(WINDOWS)
    add_subdirectory(windows)
elseif(LINUX)
    add_subdirectory(linux)
endif()