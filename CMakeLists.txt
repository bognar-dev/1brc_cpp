cmake_minimum_required(VERSION 3.22)

project(1brc_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

cmake_minimum_required(VERSION 3.22)

project(1brc_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

find_package(benchmark REQUIRED)
add_executable(1brc_cpp main.cpp

        )
add_executable(1_BRC_Benchmark benchmark.cpp
        )
target_link_libraries(1_BRC_Benchmark benchmark::benchmark)
