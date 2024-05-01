cmake_minimum_required(VERSION 3.10)

project(PerformanceAnalysis)


add_executable(create-sample create-sample.c
        create-sample.c)
add_executable(main main.c
        main.c)

add_executable(v2 v2.c
        v2.c)
add_executable(v3 v3.c
        v3.c)


set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native -mtune=native -flto -Wall -Wextra -Wpedantic -Wformat=2 -Wconversion -Wundef -Winline -Wimplicit-fallthrough")

if(DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS -fsanitize=address -fsanitize=undefined -g -fstack-protector-strong")
endif()

find_package(Threads REQUIRED)
target_link_libraries(create-sample Threads::Threads)
target_link_libraries(main Threads::Threads)



