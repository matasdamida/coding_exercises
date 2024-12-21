cmake_minimum_required(VERSION 3.29)

project(hashmap CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file (GLOB_RECURSE hashmap_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE hashmap_HEADERS CONFIGURE_DEPENDS "src/*.(hpp|inl)")

set (hashmap_INCLUDE_DIRS "")
foreach (_headerFile ${hashmap_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND hashmap_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES hashmap_INCLUDE_DIRS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(hashmap ${hashmap_SOURCES})
target_include_directories(hashmap PRIVATE ${hashmap_INCLUDE_DIRS})

