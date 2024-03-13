cmake_minimum_required(VERSION 3.25)

project(1brc_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")


add_executable(1brc_cpp main.cpp)
