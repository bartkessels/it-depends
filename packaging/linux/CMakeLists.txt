cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# Generate the itdepends.yml file
file(READ ${CMAKE_BINARY_DIR}/packaging/linux/itdepends-template.yml TEMPLATE)

string(REPLACE "{binary-name}" "${CMAKE_PROJECT_NAME}" TEMPLATE "${TEMPLATE}")
string(REPLACE "{binary-version}" "v${CMAKE_PROJECT_VERSION}" TEMPLATE "${TEMPLATE}")

file(WRITE ${CMAKE_BINARY_DIR}/packaging/linux/itdepends.yml ${TEMPLATE})