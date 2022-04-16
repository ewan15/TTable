set (HEADER_LIST
        include/ttable/ttable.h
        include/ttable/simd.h
)

add_library(
        TTable
        STATIC
        lib/ttable.cpp
        ${HEADER_LIST}
)
target_link_libraries(TTable ${Boost_LIBRARIES})

include_directories(${Boost_INCLUDE_DIRS})

target_include_directories(TTable INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
