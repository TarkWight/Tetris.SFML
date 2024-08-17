cmake_minimum_required(VERSION 3.28)
project(Tetris_SFML)

set(CMAKE_CXX_STANDARD 23)

# Set SFML_DIR for Homebrew on macOS
if(APPLE)
  set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib/cmake/SFML")
endif()

# Find SFML
find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)

# Conditional dependency inclusion
if(APPLE)
  find_package(GTest REQUIRED)
  find_package(nlohmann_json 3.9.1 REQUIRED)
  find_package(spdlog REQUIRED)
  find_package(cxxopts REQUIRED)
elseif(WIN32)
  find_package(GTest REQUIRED)
  find_package(nlohmann_json REQUIRED)
  find_package(spdlog REQUIRED)
  find_package(cxxopts REQUIRED)
endif()

# Define the executable
add_executable(Tetris_SFML
    Source/Main.cpp
    )

# Define the resource directory
target_compile_definitions(Tetris_SFML PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/Resources")

# Link libraries
target_link_libraries(Tetris_SFML
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    GTest::GTest
    GTest::Main
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    cxxopts::cxxopts
)

# Testing
#enable_testing()
#if(EXISTS ${CMAKE_SOURCE_DIR}/Tests/CMakeLists.txt)
#    add_subdirectory(Tests)
#else()
#    message(WARNING "Directory ${CMAKE_SOURCE_DIR}/Tests does not exist. Skipping #add_subdirectory(Tests).")
#endif()

# Installation
install(TARGETS Tetris_SFML DESTINATION bin)
install(DIRECTORY Source/ DESTINATION include)

# Support for CLion and Visual Studio
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
