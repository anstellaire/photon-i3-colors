#pragma once

#include <cstdint>

template<typename T>
__global__ void mat_mult_tiled(
    T const* __restrict__ a, T const* __restrict__ b, T* __restrict__ c,
    std::size_t a_height, std::size_t a_width, std::size_t b_width) {

    std::size_t const tile_size = blockDim.x;
    std::size_t const tile_x = threadIdx.x;
    std::size_t const tile_y = threadIdx.y;
    std::size_t const global_y = tile_size * blockIdx.y + tile_y;
    std::size_t const global_x = tile_size * blockIdx.x + tile_x;

    // create shared memory for a tile
    extern __shared__ T shared[];
    T* __restrict__ sh_a = shared;
    T* __restrict__ sh_b = shared + tile_size * tile_size;

    // create private variable for thread result
    T pr_result = 0;

    // process tile sequence
    for (std::size_t tile_begin = 0; tile_begin < a_width; tile_begin += tile_size) {
        // load tile to shared memory
        sh_a[tile_size * tile_y + tile_x] =
            a[a_width * global_y + tile_begin + tile_x];
        sh_b[tile_size * tile_y + tile_x] =
            b[b_width * tile_begin + b_width * tile_y + global_x];

        // wait for loading tile to shared memory
        __syncthreads();

        // process tile in shared memory
        for (std::size_t i = 0; i < tile_size; ++i)
            pr_result += sh_a[tile_size * tile_y + i] * sh_b[tile_size * i  + tile_x];

        // wait for processing tile in shared memory before loading next tile
        __syncthreads();
    }

    // write result to global memory
    c[b_width * global_y + global_x] = pr_result;
}
