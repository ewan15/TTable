//
// Created by ewan on 3/15/22.
//

#include <gtest/gtest.h>
#include <ttable/ttable.h>

TEST(TTable, initCol)
{
    auto col = TTable::column<"id", int>();
    ASSERT_EQ("id", col.name.value);
}

TEST(TTable, initTable)
{
    auto col = TTable::column<"id", int>();
    auto table = TTable::createTable<col>();
    ASSERT_EQ("id", table.col.name.value);
}

TEST(TTable, mulitColumnInitTable)
{
    auto col = TTable::column<"id", int>();
    auto col2 = TTable::column<"name", std::string>();
    auto table = TTable::createTable<col, col2>();
    ASSERT_EQ("id", table.col.name.value);
    ASSERT_EQ("name", table.tail.col.name.value);
}

TEST(TTable, getColumnByName)
{
    auto col = TTable::column<"id", int>();
    auto col2 = TTable::column<"name", std::string>();
    auto table = TTable::createTable<col, col2>();
    TTable::getColumnByName<table, "id">();
}
