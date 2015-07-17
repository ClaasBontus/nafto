cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER_INIT gcc-4.9)
set(CMAKE_CXX_COMPILER_INIT g++-4.9)

project(nafto CXX)

include_directories(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror -pedantic-errors")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=auto")
set(CMAKE_CXX_FLAGS_DEBUG "-Ofast -g -march=native -mtune=native")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -g -march=native -mtune=native")

add_subdirectory(test)
