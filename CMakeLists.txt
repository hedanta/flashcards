cmake_minimum_required(VERSION 3.18)

project(cards)

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

find_package(nlohmann_json CONFIG REQUIRED)

set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)
set(SOURCES cards.cpp)

add_executable(cards ${SOURCES})
target_link_libraries(cards PRIVATE nlohmann_json::nlohmann_json)

file(GLOB RESOURCES "cards.json")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cards.json
   ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
#file(COPY ${RESOURCES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
