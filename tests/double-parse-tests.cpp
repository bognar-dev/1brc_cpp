#include <gtest/gtest.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Regular parsing function (strtod)
double regular_parse_double(const char *s) {
    return strtod(s, nullptr);
}

// Your custom parsing function (parse_double)
static const char *parse_double(double *dest, const char *s) {
    // Your custom implementation goes here
}

// Test fixture class for parsing functions
class ParsingTest : public ::testing::Test {
protected:
// Test string
    const char *test_string = "123.456";
// Number of iterations for testing
    const int num_iterations = 1000000000;

    double regular_time;
    double custom_time;

// Set up function
    void SetUp() override {
        srand(static_cast<unsigned int>(time(nullptr)));
    }
};

// Test case to compare the runtime of regular parsing function (strtod)
TEST_F(ParsingTest, RegularParsingTime) {
    clock_t regular_start = clock();
    for (int i = 0; i < num_iterations; ++i) {
        double result = regular_parse_double(test_string);
        if (result != 0.0) {
            result += 0.0;
        }
    }
    clock_t regular_end = clock();
    regular_time = static_cast<double>(regular_end - regular_start) / CLOCKS_PER_SEC;
    std::cout << "Regular Parsing Time: " << regular_time << " seconds\n";
}

// Test case to compare the runtime of custom parsing function (parse_double)
TEST_F(ParsingTest, CustomParsingTime) {
    clock_t custom_start = clock();
    for (int i = 0; i < num_iterations; ++i) {
        double result;
        parse_double(&result, test_string);
// Prevent compiler optimization by using the result
        if (result != 0.0) {
            result += 0.0;
        }
    }
    clock_t custom_end = clock();
    custom_time = static_cast<double>(custom_end - custom_start) / CLOCKS_PER_SEC;
    std::cout << "Custom Parsing Time: " << custom_time << " seconds\n";
    // percentage speedup
    double speedup = regular_time / custom_time;
    std::cout << "Speedup: " << speedup << "\n";
}

int main(int argc, char **argv) {
    // Initialize Google Test framework
    ::testing::InitGoogleTest(&argc, argv);
    // Run tests
    return RUN_ALL_TESTS();
}
