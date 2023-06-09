cmake_minimum_required(VERSION 3.18)

project(cards)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()


set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

find_package(nlohmann_json CONFIG REQUIRED)
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)

add_executable(cards WIN32
		main.cpp
		deck_manager.hpp
		"deck_manager.cpp"
		quiz_manager.hpp
		"quiz_manager.cpp"
    main.manifest)

target_link_libraries(cards PRIVATE nlohmann_json::nlohmann_json wx::core wx::base)

find_package(wxWidgets CONFIG REQUIRED)

file(GLOB RESOURCES "cards.json")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cards.json
   ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
