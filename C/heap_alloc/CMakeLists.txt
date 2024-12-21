cmake_minimum_required(VERSION 3.29)

project(heap_alloc C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -pedantic")
set(CMAKE_C_FLAGS_DEBUG "-ggdb3 -Og")
set(CMAKE_C_FLAGS_RELEASE "-O3")

file (GLOB_RECURSE heap_alloc_SOURCES CONFIGURE_DEPENDS "src/*.c")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(heap_alloc ${heap_alloc_SOURCES})
