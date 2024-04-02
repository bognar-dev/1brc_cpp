#include <chrono>
#include <iostream>
#include "calculations.h"


int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::string input = "../data/measurements.txt";
    evaluate(input);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Execution time: " << elapsed.count() << "s" << std::endl;

    return 0;
}