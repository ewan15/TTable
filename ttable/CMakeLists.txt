set (HEADER_LIST
        include/ttable/ttable.h
)

add_library(
        TTable
        lib/ttable.cpp
        ${HEADER_LIST}
)

target_include_directories(TTable INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
