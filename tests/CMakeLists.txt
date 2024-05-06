cmake_minimum_required(VERSION 3.10)
project(Tests)

# Include Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add your test executable
add_executable(MyParsingTests
        double-parse-tests.cpp
)
target_compile_features(MyParsingTests PRIVATE cxx_std_17)
# Link Google Test libraries
target_link_libraries(MyParsingTests
        gtest_main
)

# Add Google Test to include directories
target_include_directories(MyParsingTests PRIVATE
        ${googletest_SOURCE_DIR}/googletest/include
        ${googletest_SOURCE_DIR}/googlemock/include
)


add_test(NAME Double_Parsing_GTest COMMAND MyParsingTests)