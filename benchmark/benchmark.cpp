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

static void BM_AddColumn(benchmark::State& state) {
    using col = TTable::Column<"id", int>;
    using col2 = TTable::Column<"age", int>;
    auto table = TTable::create_table<col, col2>();
    for (auto i = 0; i < ELEMENTS_PUSH_BACK; i++)
    {
        TTable::push_back(table, 5, 4);
    }

    for (auto _ : state)
    {
        auto newTable = TTable::add_column<col2>(table);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_AddColumn);

static void BM_AddTwoColumn(benchmark::State& state) {
    using Col = TTable::Column<"id", int>;
    using Col2 = TTable::Column<"age", int>;
    auto col = Col{};
    auto col2 = Col2{};
    for (auto i = 0; i < ELEMENTS_PUSH_BACK; i++)
    {
        col.vec.push_back(1);
        col2.vec.push_back(1);
    }

    for (auto _ : state)
    {
        TTable::add_two_columns<"new">(col, col2);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_AddTwoColumn);

BENCHMARK_MAIN();