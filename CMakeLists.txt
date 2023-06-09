cmake_minimum_required(VERSION 3.21)

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

find_package(wxWidgets CONFIG REQUIRED)

add_executable(cards WIN32
		main.cpp
    main.manifest)

add_subdirectory(lib)

target_link_libraries(cards PRIVATE nlohmann_json::nlohmann_json wx::core wx::base quiz_manager)

target_include_directories(cards PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:src> 
        )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src DESTINATION bin)

install(TARGETS cards DESTINATION bin)

add_custom_target(install_${PROJECT_NAME}
        ${CMAKE_COMMAND} -DCMAKE_INSTALL_CONFIG_NAME=${CMAKE_BUILD_TYPE}
        -P cmake_install.cmake
        )

#file(GLOB RESOURCES "cards.json")
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/cards.json
#   ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)