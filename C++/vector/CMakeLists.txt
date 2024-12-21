cmake_minimum_required(VERSION 3.29)

project(vector CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file (GLOB_RECURSE vector_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE vector_HEADERS CONFIGURE_DEPENDS "src/*.(hpp|inl)")

set (vector_INCLUDE_DIRS "")
foreach (_headerFile ${vector_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND vector_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES vector_INCLUDE_DIRS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(vector ${vector_SOURCES})
target_include_directories(vector PRIVATE ${vector_INCLUDE_DIRS})

