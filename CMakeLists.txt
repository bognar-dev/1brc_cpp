cmake_minimum_required(VERSION 3.20.6)

project(1brc_cpp)

set(CMAKE_CXX_STANDARD 17)

# Set the flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native -flto -Wall -Wextra -Wpedantic -Wformat=2 -Wconversion -Wundef -Winline -Wimplicit-fallthrough ")

add_definitions(-DNTHREADS=${NTHREADS})

project(1brc_cpp)


find_package(benchmark REQUIRED)
add_executable(1brc_cpp main.cpp
        calculations.cpp
        calculations.h
        channel.h
)
add_executable(1_BRC_Benchmark benchmark.cpp
        calculations.cpp
        calculations.h
        channel.h)
target_link_libraries(1_BRC_Benchmark benchmark::benchmark)