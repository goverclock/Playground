cmake_minimum_required(VERSION 3.10)
project(GChat VERSION 0.1)
add_executable(GChat server.cpp)
configure_file(server_config.h.in server_config.h)
target_include_directories(GChat PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
