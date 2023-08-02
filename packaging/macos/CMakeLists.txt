cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CPACK_BUNDLE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_GENERATOR "DragNDrop")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_DEST ${CMAKE_BINARY_DIR})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME ${CMAKE_PROJECT_NAME})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_COPYRIGHT "Bart Kessels")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE itdepends)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER "net.bartkessels.${CMAKE_PROJECT_NAME}")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_STRING ${CMAKE_PROJECT_DESCRIPTION})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING ${CMAKE_PROJECT_VERSION})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING ${CMAKE_PROJECT_VERSION_MAJOR})
set(BUNDLE_NAME ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.app)

if (use_qt6)
    get_target_property(qmake_executable Qt::qmake IMPORTED_LOCATION)
else()
    get_target_property(qmake_executable Qt5::qmake IMPORTED_LOCATION)
endif()

get_filename_component(_qt_bin_dir "${qmake_executable}" DIRECTORY)
find_program(MACDEPLOYQT_BIN macdeployqt HINT "${_qt_bin_dir}")

# Link Qt dependencies to ItDepends.app bundle
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${MACDEPLOYQT_BIN} ${BUNDLE_NAME} -always-overwrite
)

# Copy icon into ItDepends.app bundle
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND cp ${CMAKE_BINARY_DIR}/packaging/macos/icons/itdepends.icns ${BUNDLE_NAME}/Contents/Resources
)