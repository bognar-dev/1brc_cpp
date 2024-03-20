#include <chrono>
#include <iostream>
#include "calculations.h"


int main() {
    auto start = std::chrono::high_resolution_clock::now();
    auto data = readFile();
    auto afterRead = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedRead = afterRead - start;
    calcAvr(data);
    auto afterCalc = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedCalc = afterCalc - afterRead;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Reading time: " << elapsedRead.count() << "s" << std::endl;
    std::cout << "Calculation time: " << elapsedCalc.count() << "s" << std::endl;
    std::cout << "Execution time: " << elapsed.count() << "s" << std::endl;

    return 0;
}