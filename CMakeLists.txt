cmake_minimum_required(VERSION 3.26)
project(Tetris_SFML)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)
if(NOT DEFINED ENV{SFML_ROOT})
  message(FATAL_ERROR "is not found")
else()
  set(SFML_DIR "$ENV{SFML_ROOT}/lib/cmake/SFML")
endif()

add_executable(Tetris_SFML
Source/Main.cpp
)

target_link_libraries(Tetris_SFML
sfml-system
sfml-window
sfml-graphics)

target_compile_definitions(Tetris_SFML PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/Resources")