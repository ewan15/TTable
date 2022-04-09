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
    std::vector<T> vec;
    T t;
};

template <typename Col, typename Tail> struct Table
{
    Col col;
    Tail t;
};
struct None
{
};

template <typename Col> auto create_table()
{
    return Table<Col, None>();
}

template <typename Col, typename Col2, typename... Cols> auto create_table()
{
    using tail = typeof(create_table<Col2, Cols...>());
    return Table<Col, tail>();
}

// TODO: Make reference?
template <StringLiteral name> auto get_column_by_name(auto table)
{
    static_assert(!std::is_same<typeof(table), None>(), "cannot find column");

    if constexpr (std::string_view(table.col.name.value) == name.value)
        return table.col;
    else
        return get_column_by_name<name>(table.t);
}

template <typename T, typename... Ts> void push_back(auto &table, T &&row, Ts &&...rows)
{
    table.col.vec.push_back(row);
    static_assert(std::is_same<typeof(table.t), None>(), "missing elements to insert");
}

template <typename T, typename T2, typename... Ts> void push_back(auto &table, T &&row, T2 &&row2, Ts &&...rows)
{
    table.col.vec.push_back(row);
    push_back(table.t, row2, rows...);
}

template <StringLiteral n, typename T> struct RowElement
{
    static constexpr auto name = n;
    T val;
};

template <typename Col, typename Tail> struct Row
{
    Col col;
    Tail t;
};

auto get_row_typed(auto table, std::size_t index)
{
    if constexpr (std::is_same<typeof(table), None>())
    {
        return None{};
    }

    else
    {
        auto tail = get_row_typed(table.t, index);
        using T = typeof(table.col.t);
        auto rowElement = RowElement<table.col.name, T>{.val = table.col.vec.at(index)};
        return Row<typeof(rowElement), typeof(tail)>{.col = rowElement, .t = tail};
    }
}

auto get_row(auto table, std::size_t index)
{
    return get_row_typed(table, index);
}
} // namespace TTable

#endif // TTABLE_TTABLE_H
