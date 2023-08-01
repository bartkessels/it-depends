cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

if (APPLE)
    include(${CMAKE_SOURCE_DIR}/packaging/macos/CMakeLists.txt)
#    add_subdirectory(macos)
elseif(WINDOWS)
    include(${CMAKE_SOURCE_DIR}/packaging/windows/CMakeLists.txt)
elseif(LINUX)
    include(${CMAKE_SOURCE_DIR}/packaging/linux/CMakeLists.txt)
endif()