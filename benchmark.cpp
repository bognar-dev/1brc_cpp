
#include <benchmark/benchmark.h>
#include "calculations.h"


class One_BRC : public benchmark::Fixture {
protected:

public:
    void SetUp(::benchmark::State &state) {
    }

    void TearDown(::benchmark::State &state) {
    }
};

BENCHMARK_DEFINE_F(One_BRC,evaluate )(benchmark::State &st) {
    for (auto _: st) {

    }

    const char *file = "/app/data/measurements.txt";
    evaluate(file);
}

BENCHMARK_REGISTER_F(One_BRC, evaluate);
BENCHMARK_MAIN();