
#include <benchmark/benchmark.h>
#include <chrono>
#include "calculations.h"

class One_BRC : public benchmark::Fixture {
protected:
    std::map<std::string, std::vector<float>> _data;
public:
    void SetUp(::benchmark::State &state) {

    }

    void TearDown(::benchmark::State &state) {
    }
};

BENCHMARK_F(One_BRC, readFile)(benchmark::State &st) {
    for (auto _: st) {
        _data = readFile();
    }
}

BENCHMARK_F(One_BRC, calculateAverages)(benchmark::State &st) {
    for (auto _: st) {
        calcAvr(_data);
    }
}


BENCHMARK_MAIN();