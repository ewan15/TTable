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

template <StringLiteral n, typename T> struct Column
{
    static constexpr auto name = n;
    std::vector<T> vec;
    using Type = T;
};

template<StringLiteral name, typename T1, typename T2, StringLiteral col1Name, StringLiteral col2Name>
Column<name, T1> add_two_columns (Column<col1Name, T1> const& col1, Column<col2Name, T2> const& col2) {
    static_assert(std::is_same<T1,T2>(), "incompatible types");
    using NewCol = TTable::Column<name, T1>;
    auto newCol = NewCol {
        .vec = std::vector<T1>(col1.vec.size())
    };
    for (auto i = 0; i < col1.size()-1; i++) {
        newCol[i] = col1.vec[i] + col2.vec[i];
    }
    return newCol;
}

template <typename Col, typename Tail> struct Table
{
    Col col;
    Tail t;
};
struct None
{
};


template <typename Col, typename Tail>
std::ostream &operator<<(std::ostream &os, Table<Col, Tail> const &m) {
    return os << "|" << m.col.name.value;
}

std::ostream &operator<<(std::ostream &os, None const &m) {
    return os << "|";
}

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
        using T = typeof(table.col);
        using Type = typename T::Type;
        auto rowElement = RowElement<table.col.name, Type>{.val = table.col.vec.at(index)};
        return Row<typeof(rowElement), typeof(tail)>{.col = rowElement, .t = tail};
    }
}

auto get_row(auto table, std::size_t index)
{
    return get_row_typed(table, index);
}
template <StringLiteral name> auto get_col_from_row(auto row)
{
    if constexpr (std::string_view(row.col.name.value) == name.value)
        return row.col.val;
    else
        return get_col_from_row<name>(row.t);
}
// TODO
auto add_column(auto table) {

}
// TODO
auto drop_column() {

}
} // namespace TTable

#endif // TTABLE_TTABLE_H
