//
// Created by Ewan Bains on 3/15/22.
//

#ifndef TTABLE_TTABLE_H
#define TTABLE_TTABLE_H

// Example type: TTable::TTable<"id", int, "name", string>()
#include <algorithm>
#include <boost/align/aligned_allocator.hpp>
#include <cstdlib>

#include <ttable/simd.h>

namespace TTable
{

template <std::size_t N>
struct StringLiteral
{
    constexpr StringLiteral(const char (&str)[N])
    {
        std::copy_n(str, N, value);
    }

    char value[N];
    std::size_t len = N;
};

template <StringLiteral n, typename T>
struct Column
{
    static constexpr auto name = n;
    std::vector<T> vec;
    using Type = T;
};

template <StringLiteral name, typename T1, typename T2, StringLiteral col1Name, StringLiteral col2Name>
Column<name, T1> transform_two_columns(Column<col1Name, T1> const &col1, Column<col2Name, T2> const &col2, auto& operation)
{
    static_assert(std::is_same<T1, T2>(), "incompatible types");
    using NewCol = TTable::Column<name, T1>;
    const auto size = col1.vec.size();
    auto newCol = NewCol{.vec = std::vector<T1>(size)};
    for (std::size_t i = 0; i < size; ++i)
    {
        newCol.vec[i] = operation(col1.vec[i], col2.vec[i]);
    }
    return newCol;
}

template <StringLiteral name, typename T1, typename T2, StringLiteral col1Name, StringLiteral col2Name>
Column<name, T1> add_two_columns(Column<col1Name, T1> const &col1, Column<col2Name, T2> const &col2)
{
    const auto operation = [](T1 a, T2 b){return a+b;};
    return transform_two_columns<name, T1, T2, col1Name, col2Name>(col1, col2, operation);
}

template <StringLiteral name, typename T1, typename T2, StringLiteral col1Name, StringLiteral col2Name>
Column<name, T1> minus_two_columns(Column<col1Name, T1> const &col1, Column<col2Name, T2> const &col2)
{
    const auto operation = [](T1 a, T2 b){return a-b;};
    return transform_two_columns<name, T1, T2, col1Name, col2Name>(col1, col2, operation);
}


template <typename Col, typename Tail>
struct Table
{
    Col col;
    Tail t;
};
struct None
{
};

template <typename Col, typename Tail>
std::ostream &operator<<(std::ostream &os, Table<Col, Tail> const &m)
{
    return os << std::string_view("|") << std::string_view(m.col.name.value);
}

std::ostream &operator<<(std::ostream &os, None const &m)
{
    return os << std::string_view("|");
}

template <typename Col>
auto create_table()
{
    return Table<Col, None>();
}

template <typename Col, typename Col2, typename... Cols>
auto create_table()
{
    using tail = typeof(create_table<Col2, Cols...>());
    return Table<Col, tail>();
}

template <StringLiteral name>
auto get_column_by_name(auto table)
{
    static_assert(!std::is_same<typeof(table), None>(), "cannot find column");

    if constexpr (std::string_view(table.col.name.value) == name.value)
        return table.col;
    else
        return get_column_by_name<name>(table.t);
}

template <typename T, typename... Ts>
void push_back(auto &table, T &&row, Ts &&...rows)
{
    table.col.vec.push_back(row);
    static_assert(std::is_same<typeof(table.t), None>(), "missing elements to insert");
}

template <typename T, typename T2, typename... Ts>
void push_back(auto &table, T &&row, T2 &&row2, Ts &&...rows)
{
    table.col.vec.push_back(row);
    push_back(table.t, row2, rows...);
}

template <StringLiteral n, typename T>
struct RowElement
{
    static constexpr auto name = n;
    T val;
};

template <typename Col, typename Tail>
struct Row
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

template <StringLiteral name>
auto get_col_from_row(auto row)
{
    if constexpr (std::string_view(row.col.name.value) == name.value)
        return row.col.val;
    else
        return get_col_from_row<name>(row.t);
}

void move_column(auto &source, auto &target)
{
    if constexpr (std::is_same<typeof source, None>() || std::is_same<typeof target, None>())
    {
        return;
    }
    else
    {
        target.col.vec = source.col.vec;
        move_column(source.t, target.t);
    }
}

template <typename col>
auto add_column(auto table)
{
    using NewTableType = Table<col, typeof table>;
    auto newTable = NewTableType{};
    newTable.col = col{};
    newTable.col.vec.resize(table.col.vec.size());
    move_column(table, newTable.t);
    return newTable;
}

template <StringLiteral name>
auto drop_column(auto table)
{
    if constexpr (std::is_same<typeof table, None>())
    {
        static_assert(true, "unable to find column name");
    }
    else if constexpr (std::string_view(table.col.name.value) == name.value)
    {
        return table.t;
    }
    else
    {
        const auto col = drop_column<name>(table.t);
        return Table<typeof table.col, typeof col>{.col = table.col, .t = col};
    }
}
} // namespace TTable

#endif // TTABLE_TTABLE_H
