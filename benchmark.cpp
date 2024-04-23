
#include <benchmark/benchmark.h>
#include <chrono>
#include "calculations.h"


std::map<std::string, std::vector<float>> data;
class One_BRC : public benchmark::Fixture {
protected:

public:
    void SetUp(::benchmark::State &state) {
    }

    void TearDown(::benchmark::State &state) {
    }
};

BENCHMARK_DEFINE_F(One_BRC, readFile)(benchmark::State &st) {
    for (auto _: st) {

    }

    std::string input = "../data/measurements.txt";
    evaluate(input);
    benchmark::DoNotOptimize(data);
}


BENCHMARK_DEFINE_F(One_BRC, calculateAverages)(benchmark::State &st) {
    for (auto _: st) {

    }
    //calcAvr(data);
}

BENCHMARK_REGISTER_F(One_BRC, readFile);
BENCHMARK_REGISTER_F(One_BRC, calculateAverages);
BENCHMARK_MAIN();