//
// Created by ewan on 4/16/22.
//

#ifndef TTABLE_SIMD_H
#define TTABLE_SIMD_H

#include <immintrin.h>

namespace TTable::SIMD
{
void add(int *result, const int *a, const int *b, size_t size)
{
//#pragma omp parallel for shared(a, b, c) private(i) schedule(static, 512)
    for (std::size_t i = 0; i < size; ++i)
    {
        result[i] = a[i] + b[i];
    }
}
} // namespace TTable::SIMD

#endif // TTABLE_SIMD_H
