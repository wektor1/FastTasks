cmake_minimum_required(VERSION 3.10)

project(FastTasks)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_FLAGS "-g -O0")

add_subdirectory(source)

# add_subdirectory(tests)
