//
// Created by ewan on 3/15/22.
//

#include <gtest/gtest.h>
#include <ttable/ttable.h>

TEST(TTable, initCol)
{
    using col = TTable::column<"id", int>;
    ASSERT_TRUE(std::string_view("id") == col::name.value);
}

TEST(TTable, initTable)
{
    using col = TTable::column<"id", int>;
    auto table = TTable::create_table<col>();
    ASSERT_TRUE(std::string_view("id") == table.col.name.value);
}

TEST(TTable, mulitColumnInitTable)
{
    using col = TTable::column<"id", int>;
    using col2 = TTable::column<"name", std::string>;
    auto table = TTable::create_table<col, col2>();
    ASSERT_TRUE(std::string_view("id") == table.col.name.value);
    ASSERT_TRUE(std::string_view("name") == table.t.col.name.value);
}

TEST(TTable, getColumnByName)
{
    using col = TTable::column<"id", int>;
    using col2 = TTable::column<"name", std::string>;
    auto table = TTable::create_table<col, col2>();

    auto tempCol = TTable::get_column_by_name<"id">(table);
    ASSERT_TRUE(std::string_view("id") == tempCol.name.value);

    auto tempCol2 = TTable::get_column_by_name<"name">(table);
    ASSERT_TRUE(std::string_view("name") == tempCol2.name.value);
}

TEST(TTable, push_back)
{
    using col = TTable::column<"id", int>;
    using col2 = TTable::column<"name", std::string>;
    auto table = TTable::create_table<col, col2>();

    TTable::push_back(table, 5, "test");
}

TEST(TTable, get_row)
{
    using col = TTable::column<"id", int>;
    using col2 = TTable::column<"name", std::string>;
    auto table = TTable::create_table<col, col2>();

    TTable::push_back(table, 5, "test");

    auto row = TTable::get_row(table, 0);
}
