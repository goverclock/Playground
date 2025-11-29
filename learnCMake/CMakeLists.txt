cmake_minimum_required(VERSION 3.7...3.21)
project(gmine VERSION 1.0
              DESCRIPTION "some sort of game I guess"
              LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(libhello STATIC
    src/libhello.cpp
    include/hello/lib.hpp)
target_compile_features(libhello PUBLIC cxx_std_11)

add_executable(ghello apps/hello.cpp)
target_link_libraries(ghello PUBLIC libhello)

function(SIMPLE XXX)
    message("FUCK ${XXX} ${ARGN}")
endfunction()

simple("YOU" "HE" "ME")

set(MYVAR "my var")
include(CMakePrintHelpers)

cmake_print_variables(PROJECT_NAME)
cmake_print_variables(CMAKE_PROJECT_NAME)
cmake_print_variables(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
message(STATUS "message status")
