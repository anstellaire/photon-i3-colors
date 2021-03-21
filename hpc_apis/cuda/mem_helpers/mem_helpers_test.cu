#include "mem_helpers.cuh"

#include <cassert>
#include <cstdint>
#include <vector>

template<typename T, typename F, typename K, typename C>
void test_device_memory(std::size_t num, F filler, K kernel, C checker) {
    // allocate host memory
    auto host_mem = std::vector<T>(num);

    // allocate device memory
    auto dev_mem = device_memory<T>(num);

    // launch filler
    filler(host_mem.data(), host_mem.size());

    // move from host to device
    dev_mem.from_host(host_mem.data());

    // launch kernel
    kernel(dev_mem.data(), dev_mem.size());

    // move from device to host
    dev_mem.to_host(host_mem.data());

    // launch checker
    checker(host_mem.data(), host_mem.size());
}

template<typename T, typename F, typename K, typename C>
void test_shared_memory(std::size_t num, F filler, K kernel, C checker) {
    // allocate shared memory
    auto shared_mem = shared_memory<T>(num);

    // launch filler
    filler(shared_mem.data(), shared_mem.size());

    // [optional] prefetch from host to device
    int dev_id;
    cudaGetDevice(&dev_id);
    shared_mem.advise(cudaMemAdviseSetReadMostly, dev_id);
    shared_mem.prefetch_device(dev_id);

    // launch kernel
    kernel(shared_mem.data(), shared_mem.size());

    // wait kernel completion
    cudaDeviceSynchronize();

    // [optional] prefetch from device to host
    shared_mem.prefetch_host();

    // launch checker
    checker(shared_mem.data(), shared_mem.size());
}

template<typename T, typename F, typename K, typename C>
void test_pinned_memory(std::size_t num, F filler, K kernel, C checker) {
    // allocate host memory
    auto pinned_mem = pinned_memory<T>(num);

    // allocate device memory
    auto dev_mem = device_memory<T>(num);

    // launch filler
    filler(pinned_mem.data(), pinned_mem.size());

    // move from host to device
    dev_mem.from_host(pinned_mem.data());

    // launch kernel
    kernel(dev_mem.data(), dev_mem.size());

    // move from device to host
    dev_mem.to_host(pinned_mem.data());

    // launch checker
    checker(pinned_mem.data(), pinned_mem.size());
}

template<typename T>
__global__ void test_kernel(T* vec, std::size_t num) {
    std::size_t i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < num)
        vec[i] = i;
}

int main() {
    using test_type = int;

    auto filler = [](test_type* host_mem, std::size_t num) {
        for (std::size_t i = 0; i < num; ++i)
            host_mem[i] = 0;
    };

    auto checker = [](test_type* host_mem, std::size_t num) {
        for (std::size_t i = 0; i < num; ++i)
            assert(host_mem[i] == i);
    };

    auto kernel = [](test_type* dev_mem, std::size_t num) {
        std::size_t const block_size = 32 * 32;
        std::size_t const grid_size = (num + block_size - 1) / block_size;
        test_kernel<<<grid_size, block_size>>>(dev_mem, num);
    };

    test_device_memory<test_type>(1 << 16, filler, kernel, checker);
    test_shared_memory<test_type>(1 << 16, filler, kernel, checker);
    test_pinned_memory<test_type>(1 << 16, filler, kernel, checker);
}
