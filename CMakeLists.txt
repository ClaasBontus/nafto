cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER_INIT gcc-4.9)
set(CMAKE_CXX_COMPILER_INIT g++-4.9)

project(nafto CXX)

include_directories(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror -pedantic-errors")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=auto -Ofast -g")

add_subdirectory(test)
add_subdirectory(benchmarks)
