//
// Created by ewan on 3/15/22.
//

#include <gtest/gtest.h>
#include <ttable/ttable.h>

TEST(TTable, initCol)
{
    auto col = TTable::column<"id", int>();
    ASSERT_TRUE(std::string_view("id") == col.name.value);
}

TEST(TTable, initTable)
{
    auto col = TTable::column<"id", int>();
    auto table = TTable::createTable<col>();
    ASSERT_TRUE(std::string_view("id") == table.col.name.value);
}

TEST(TTable, mulitColumnInitTable)
{
    auto col = TTable::column<"id", int>();
    auto col2 = TTable::column<"name", std::string>();
    auto table = TTable::createTable<col, col2>();
    ASSERT_TRUE(std::string_view("id") == table.col.name.value);
    ASSERT_TRUE(std::string_view("name") == table.tail.col.name.value);
}

TEST(TTable, getColumnByName)
{
    auto col = TTable::column<"id", int>();
    auto col2 = TTable::column<"name", std::string>();
    auto table = TTable::createTable<col, col2>();

    auto tempCol = TTable::getColumnByName<table, "id">();
    ASSERT_TRUE(std::string_view("id") == tempCol.name.value);

    auto tempCol2 = TTable::getColumnByName<table, "name">();
    ASSERT_TRUE(std::string_view("name") == tempCol2.name.value);
}

TEST(TTable, push_back)
{
    auto col = TTable::column<"id", int>();
    auto col2 = TTable::column<"name", std::string>();
    auto table = TTable::createTable<col, col2>();

    TTable::push_back<table>(5,"test");
}
