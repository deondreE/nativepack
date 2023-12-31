cmake_minimum_required(VERSION 3.16)

project(Nativepack LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/tomlplusplus)

add_executable(main src/main.cpp src/config.h src/config.cpp src/logger.h src/logger.cpp src/core.h)

target_include_directories(main PRIVATE vendor/tomlplusplus/include)
