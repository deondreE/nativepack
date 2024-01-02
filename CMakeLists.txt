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
add_subdirectory(vendor/tomlplusplus vendor/json)

# Testing Executable.
enable_testing()

# Test glob
file(GLOB TEST_SOURCE "__tests__/*.cc")

add_executable(tests ${TEST_SOURCE})
target_link_libraries(tests GTest::gtest_main)

target_include_directories(tests PRIVATE vendor/tomlplusplus/include vendor/json)

include(GoogleTest)
gtest_discover_tests(tests)

# File Globs
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

# Main Executable.
add_executable(main ${SOURCES} ${HEADERS})

target_include_directories(main PRIVATE vendor/tomlplusplus/include vendor/json/single_include)
