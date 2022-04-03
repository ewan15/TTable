//
// Created by Ewan Bains on 3/15/22.
//

#ifndef TTABLE_TTABLE_H
#define TTABLE_TTABLE_H

// Example type: TTable::TTable<"id", int, "name", string>()
#include <algorithm>
#include <cstdlib>

namespace TTable
{
template <std::size_t N> struct StringLiteral
{
    constexpr StringLiteral(const char (&str)[N])
    {
        std::copy_n(str, N, value);
    }

    char value[N];
    std::size_t len = N;
};

template <StringLiteral n, typename T> struct column
{
    static constexpr auto name = n;
    static std::vector<T> vec;
};

template <auto c, auto t> struct Table
{
    static constexpr auto col = c;
    static constexpr auto tail = t;
};

template <StringLiteral n, typename T> struct Row
{
    static constexpr auto name = n;
    static T vec;
};

template <auto col> auto createTable()
{
    return Table<col, nullptr>();
}

template <auto col, auto col2, auto... cols> auto createTable()
{
    auto tail = createTable<col2, cols...>();
    return Table<col, tail>();
}

template <auto table, StringLiteral name> auto getColumnByName()
{
    if constexpr (table.col.name.len == name.len && std::string_view(table.col.name.value) == name.value)
        return table.col;
    else
        return getColumnByName<table.tail, name>();
}

template <auto table, typename T, typename... Ts>
void push_back(T&& row, Ts&&... rows) {
    table.col.vec.push_back(row);
}

template <auto table, typename T, typename T2, typename... Ts>
void push_back(T&& row, T2&& row2, Ts&&... rows) {
    table.col.vec.push_back(row);
    push_back<table.tail>(row2, rows...);
}
} // namespace TTable

#endif // TTABLE_TTABLE_H
