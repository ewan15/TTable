enable_testing()

add_executable(
        TTableTest
        ttableTest.cpp
)
target_link_libraries(
        TTableTest
        TTable
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(TTableTest)
