set (HEADER_LIST
        include/ttable/ttable.h
)

add_library(
        TTable
        lib/ttable.cpp
)

include_directories(include)
