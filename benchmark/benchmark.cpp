#include <benchmark/benchmark.h>
#include <ttable/ttable.h>

static void BM_SinglePushBack(benchmark::State& state) {
    for (auto _ : state)
    {
        using col = TTable::Column<"id", int>;
        using col2 = TTable::Column<"name", std::string>;
        auto table = TTable::create_table<col, col2>();

        TTable::push_back(table, 5, "test");
    }
}
// Register the function as a benchmark
BENCHMARK(BM_SinglePushBack);

#define ELEMENTS_PUSH_BACK 1000
static void BM_MultiPushBack(benchmark::State& state) {
    for (auto _ : state)
    {
        using col = TTable::Column<"id", int>;
        using col2 = TTable::Column<"name", std::string>;
        auto table = TTable::create_table<col, col2>();

        for (auto i = 0; i < ELEMENTS_PUSH_BACK; i++)
        {
            TTable::push_back(table, 5, "test");
        }
    }
}
// Register the function as a benchmark
BENCHMARK(BM_MultiPushBack);

BENCHMARK_MAIN();