cmake_minimum_required(VERSION 3.29)

project(vector CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file (GLOB_RECURSE vector_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(vector ${vector_SOURCES})
