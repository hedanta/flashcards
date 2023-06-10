add_library(deck_manager deck_manager.cpp include/quiz/deck_manager.hpp)
target_link_libraries(deck_manager PRIVATE nlohmann_json::nlohmann_json)

set_property(TARGET deck_manager PROPERTY CXX_STANDARD 17)

target_include_directories(deck_manager PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

add_library(quiz_manager quiz_manager.cpp include/quiz/quiz_manager.hpp)

target_link_libraries(quiz_manager PRIVATE nlohmann_json::nlohmann_json deck_manager)

set_property(TARGET quiz_manager PROPERTY CXX_STANDARD 17)

target_include_directories(quiz_manager PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS deck_manager quiz_manager)
