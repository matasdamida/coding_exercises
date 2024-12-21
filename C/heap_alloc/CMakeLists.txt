cmake_minimum_required(VERSION 3.29)

project(heap_alloc C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -pedantic")
set(CMAKE_C_FLAGS_DEBUG "-ggdb3 -Og")
set(CMAKE_C_FLAGS_RELEASE "-O3")

file (GLOB_RECURSE heap_alloc_SOURCES CONFIGURE_DEPENDS "src/*.c")
file (GLOB_RECURSE heap_alloc_HEADERS CONFIGURE_DEPENDS "src/*.h")

set (heap_alloc_INCLUDE_DIRS "")
foreach (_headerFile ${heap_alloc_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND heap_alloc_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES heap_alloc_INCLUDE_DIRS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(heap_alloc ${heap_alloc_SOURCES})
target_include_directories(heap_alloc PRIVATE ${heap_alloc_INCLUDE_DIRS})

