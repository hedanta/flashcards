cmake_minimum_required(VERSION 3.18)

project(cards)

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

find_package(nlohmann_json CONFIG REQUIRED)
find_package(wxWidgets CONFIG REQUIRED)

set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)
set(SOURCES "main.cpp")

add_executable(cards WIN32 ${SOURCES})
target_link_libraries(cards PRIVATE nlohmann_json::nlohmann_json wx::core wx::base)

file(GLOB RESOURCES "cards.json")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cards.json
   ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
#file(COPY ${RESOURCES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
