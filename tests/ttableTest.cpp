//
// Created by ewan on 3/15/22.
//

#include <gtest/gtest.h>
#include <ttable/ttable.h>

TEST(TTable, initCol)
{
    using col = TTable::Column<"id", int>;
    ASSERT_TRUE(std::string_view("id") == col::name.value);
}

TEST(TTable, initTable)
{
    using col = TTable::Column<"id", int>;
    auto table = TTable::create_table<col>();
    ASSERT_TRUE(std::string_view("id") == table.col.name.value);
}

TEST(TTable, mulitColumnInitTable)
{
    using col = TTable::Column<"id", int>;
    using col2 = TTable::Column<"name", std::string>;
    auto table = TTable::create_table<col, col2>();
    ASSERT_TRUE(std::string_view("id") == table.col.name.value);
    ASSERT_TRUE(std::string_view("name") == table.t.col.name.value);
}

TEST(TTable, getColumnByName)
{
    using col = TTable::Column<"id", int>;
    using col2 = TTable::Column<"name", std::string>;
    auto table = TTable::create_table<col, col2>();

    auto tempCol = TTable::get_column_by_name<"id">(table);
    ASSERT_TRUE(std::string_view("id") == tempCol.name.value);

    auto tempCol2 = TTable::get_column_by_name<"name">(table);
    ASSERT_TRUE(std::string_view("name") == tempCol2.name.value);
}

TEST(TTable, push_back)
{
    using col = TTable::Column<"id", int>;
    using col2 = TTable::Column<"name", std::string>;
    auto table = TTable::create_table<col, col2>();

    TTable::push_back(table, 5, "test");
}

TEST(TTable, get_row)
{
    using col = TTable::Column<"id", int>;
    using col2 = TTable::Column<"name", std::string>;
    auto table = TTable::create_table<col, col2>();

    TTable::push_back(table, 5, "test");

    auto row = TTable::get_row(table, 0);
}

TEST(TTable, get_col_from_row)
{
    using col = TTable::Column<"id", int>;
    using col2 = TTable::Column<"name", std::string>;
    auto table = TTable::create_table<col, col2>();

    TTable::push_back(table, 5, "test");

    auto row = TTable::get_row(table, 0);
    auto name = TTable::get_col_from_row<"name">(row);
    auto id = TTable::get_col_from_row<"id">(row);

    ASSERT_EQ(name, "test");
    ASSERT_EQ(id, 5);
}

TEST(TTable, adding_two_columns)
{
    using IdCol = TTable::Column<"id", int>;
    using AgeCol = TTable::Column<"age", int>;
    // Inserting 12 values
    auto idCol = IdCol{.vec = {5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6}};
    auto ageCol = AgeCol{.vec = {4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7}};
    auto newCol = TTable::add_two_columns<"new_col">(idCol, ageCol);
    const auto correctValues = std::vector<int>{9, 7, 5, 3, 1, 1, 3, 5, 7, 9, 11, 13};
    ASSERT_TRUE(newCol.vec == correctValues);
}

TEST(TTable, minus_two_columns)
{
    using IdCol = TTable::Column<"id", int>;
    using AgeCol = TTable::Column<"age", int>;
    // Inserting 12 values
    auto idCol = IdCol{.vec = {5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6}};
    auto ageCol = AgeCol{.vec = {4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7}};
    auto newCol = TTable::minus_two_columns<"new_col">(idCol, ageCol);
    const auto correctValues = std::vector<int>{1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1};
    ASSERT_TRUE(newCol.vec == correctValues);
}

TEST(TTable, new_table_from_existing)
{
    using IdCol = TTable::Column<"id", int>;
    auto table = TTable::create_table<IdCol>();
    TTable::push_back(table, 5);
    using AgeCol = TTable::Column<"age", int>;
    auto newTable = TTable::add_column<AgeCol>(table);

    ASSERT_EQ(newTable.t.col.vec[0], 5);
    ASSERT_EQ(newTable.col.vec[0], 0);
}

TEST(TTable, drop_column)
{
    using IdCol = TTable::Column<"id", int>;
    using AgeCol = TTable::Column<"age", int>;
    auto table = TTable::create_table<IdCol, AgeCol>();
    TTable::push_back(table, 5, 6);

    auto newTable = TTable::drop_column<"age">(table);

    const auto idCol = TTable::get_column_by_name<"id">(newTable);
    //    This line should fail
    //    TTable::get_column_by_name<"age">(newTable);
    ASSERT_EQ(idCol.vec[0], 5);
}

TEST(TTable, vector_data_alignment)
{
    //using IdCol = TTable::Column<"id", int>;
    //using AgeCol = TTable::Column<"age", int>;
    //// Inserting 12 values
    //auto idCol = IdCol{.vec = {5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6}};
    //auto ageCol = AgeCol{.vec = {4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7}};
    //auto alignment = (uintptr_t)idCol.vec.data() % 512;
    //std::cout << "alignment: " << alignment << std::endl;
    //auto newCol = TTable::add_two_columns<"new_col">(idCol, ageCol);
    //const auto correctValues = TTable::Vector<int>{9, 7, 5, 3, 1, 1, 3, 5, 7, 9, 11, 13};
    //ASSERT_TRUE(newCol.vec == correctValues);
}