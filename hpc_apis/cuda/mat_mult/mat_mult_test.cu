#include "mat_mult.cuh"

#include <vector>
#include <memory>

template<typename T>
std::unique_ptr<T, void(*)(T*)> create_dev_mem(std::size_t num) {
    T* ptr = NULL;
    cudaMalloc(&ptr, num*sizeof(T));

    return std::unique_ptr<T, void(*)(T*)>{ptr, [](T* ptr){
        cudaFree(ptr);
    }};
}

template<typename Type>
void test_for(std::size_t const a_height, std::size_t const a_width, std::size_t const b_width) {

    // allocate host memory
    std::vector<Type> host_a(a_height*a_width);
    std::vector<Type> host_b(a_width*b_width);
    std::vector<Type> host_c(a_height*b_width);

    // fill host memory
    for(Type& val : host_a) val = std::rand() % 100;
    for(Type& val : host_b) val = std::rand() % 100;

    // allocate device memory
    auto dev_a = create_dev_mem<Type>(a_height*a_width);
    auto dev_b = create_dev_mem<Type>(a_width*b_width);
    auto dev_c = create_dev_mem<Type>(a_height*b_width);

    // move from host to device
    cudaMemcpy(dev_a.get(), host_a.data(), host_a.size()*sizeof(Type), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b.get(), host_b.data(), host_b.size()*sizeof(Type), cudaMemcpyHostToDevice);

    // launch kernel
    mat_mult(dev_a.get(), dev_b.get(), dev_c.get(), a_height, a_width, b_width);

    // move from device to host
    cudaMemcpy(host_c.data(), dev_c.get(), host_c.size()*sizeof(Type), cudaMemcpyDeviceToHost);

    // check result
    verify_mat_mult(host_a.data(), host_b.data(), host_c.data(), a_height, a_width, b_width);
}

int main() {
    test_for<int>(/*a_height*/1024, /*a_width*/2048, /*b_width*/512);
}
