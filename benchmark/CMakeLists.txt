add_executable(ttable_benchmark benchmark.cpp)
target_link_libraries(ttable_benchmark
        TTable
        benchmark
)
