# TTable
100% Compile time typed dataframe like tables.

## How to use

### Create a table schema
```c++
# Create all column types
using id_col = TTable::column<"id", int>;
using name_col = TTable::column<"name", std::string>;
# Create table with columns
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

### Note

More examples in tests.
