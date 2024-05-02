cmake_minimum_required(VERSION 3.10)

project(1BRC)


add_executable(create-sample create-sample.c)


add_executable(linear-search linear-search.c)

add_executable(hashmap hashmap.c)

add_executable(parse-double parse-double.c)

add_executable(fread-chunks fread-chunks.c)

add_executable(loop-unrolling loop-unrolling.c)

add_executable(parallelize parallelize.c)

add_executable(mmap mmap.c)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native -mtune=native -flto -Wall -Wextra -Wpedantic -Wformat=2 -Wconversion -Wundef -Winline -Wimplicit-fallthrough")

if(DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS -fsanitize=address -fsanitize=undefined -g -fstack-protector-strong")
endif()

find_package(Threads REQUIRED)
target_link_libraries(create-sample m Threads::Threads)
target_link_libraries(linear-search m Threads::Threads)
target_link_libraries(hashmap m Threads::Threads)
target_link_libraries(parse-double m Threads::Threads)
target_link_libraries(fread-chunks m Threads::Threads)
target_link_libraries(loop-unrolling m Threads::Threads)
target_link_libraries(parallelize m Threads::Threads)
target_link_libraries(mmap m Threads::Threads)


