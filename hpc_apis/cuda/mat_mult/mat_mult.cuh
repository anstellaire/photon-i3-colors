#pragma once

#include "mat_mult_tiled.cuh"

#include <cstdint>
#include <cassert>

template<typename T>
void mat_mult(
    T const* a, T const* b, T* c,
    std::size_t a_height, std::size_t a_width, std::size_t b_width) {

    dim3 const block_size(32u, 32u);
    dim3 const grid_size(b_width / block_size.x, a_height / block_size.y);
    auto const shared_mem_size = (2 * block_size.x * block_size.y) * sizeof(T);

    mat_mult_tiled<<<grid_size, block_size, shared_mem_size>>>(
        a, b, c, a_height, a_width, b_width);
}

template<typename T>
void verify_mat_mult(
    T const* a, T const* b, T* c,
    std::size_t a_height, std::size_t a_width, std::size_t b_width) {

    for (std::size_t i = 0; i < a_height; ++i) {
        for (std::size_t j = 0; j < b_width; ++j) {
            T result = 0;
            for (std::size_t k = 0; k < a_width; ++k)
                result += a[a_width * i + k] * b[b_width * k + j];
            assert(result == c[b_width * i + j]);
        }
    }
}
