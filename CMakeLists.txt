cmake_minimum_required(VERSION 3.16)

project(Nativepack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# Testing things
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# vendor / external sources.
add_subdirectory(vendor/tomlplusplus)

# Testing Executable.
enable_testing()

add_executable(tests __tests__/config_test.cc)
target_link_libraries(tests GTest::gtest_main)

target_include_directories(tests PRIVATE vendor/tomlplusplus/include)

include(GoogleTest)
gtest_discover_tests(tests)

# Main Executable.
add_executable(main src/main.cpp src/config.h src/config.cpp src/logger.h src/core.h src/cli.h)

target_include_directories(main PRIVATE vendor/tomlplusplus/include)
