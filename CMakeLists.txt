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
		main_app.cpp
    main_app.hpp
    main.manifest)

add_subdirectory(lib)

target_link_libraries(cards PRIVATE wx::core wx::base quiz_manager)

install(FILES cards.json DESTINATION bin)

install(TARGETS cards DESTINATION bin)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/ 
        DESTINATION bin/
        FILES_MATCHING 
        PATTERN "*.dll")

add_custom_target(install_${PROJECT_NAME}
        ${CMAKE_COMMAND} -DCMAKE_INSTALL_CONFIG_NAME=${CMAKE_BUILD_TYPE}
        -P cmake_install.cmake
        )

file(GLOB RESOURCES "cards.json")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cards.json
   ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)