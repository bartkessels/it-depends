cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(EXECUTABLE_NAME ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.exe)

get_target_property(qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_BIN windeployqt HINT "${_qt_bin_dir}")

# Link Qt dependencies to It Depends executable
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${WINDEPLOYQT_BIN} ${EXECUTABLE_NAME} -always-overwrite
)