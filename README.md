# TTable
100% Compile time typed dataframe like tables.

## What is this?
When accesing columns in a table-like structure we have two options. Create
a generic `unordered_map<vector<T>>` approach or a struct of type listed below.
```c++
struct Table {
  std::vector<int> id;
  std::vector<std::string> name;
}
```
Both are problematic.

The first introduces the problem of attempting to get a column which doesn't
exist resulting in undefined behaviour.
The second introduces the problem of cluttering the namespace with many tables
of different types.

TTable attempts to allow users to create tables on the fly and typing checking
all inserts and columns. If a column is added midway through the code the column will only exist there and will be unaccessable before.

## How to use

### Create a table schema
```c++
// Create all column types
using id_col = TTable::column<"id", int>;
using name_col = TTable::column<"name", std::string>;
// Create table with columns
auto table = TTable::create_table<id_col, name_col>();
```

### Insert into table

```c++
TTable::push_back(table, 5, "test");
```

### Fetch first row
```c++
auto row = TTable::get_row(table, 0);
auto id = TTable::get_col_from_row<"id">(row);
auto name = TTable::get_col_from_row<"name">(row);
std::cout << "id: " << id << " name: " << name << std::endl;
```

## Importing with CMake
```commandline
git clone git@github.com:ewan15/TTable.git
```
```cmake
add_subdirectory(TTable)
target_link_libraries(
        <Your Project>
        TTable
)
```

### Note

More examples in tests.
