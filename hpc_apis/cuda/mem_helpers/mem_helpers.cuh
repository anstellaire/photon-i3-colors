#pragma once

#include <memory>
#include <utility>

template<typename T>
class memory_holder {

    std::unique_ptr<T, void(*)(T*)> ptr_;
    std::size_t size_;

public:

    memory_holder(std::unique_ptr<T, void(*)(T*)> ptr, std::size_t size) :
        ptr_(std::move(ptr)), size_(size) {}

    T* data() { return ptr_.get(); }
    T const* data() const { return ptr_.get(); }
    std::size_t size() const { return size_; }
    std::size_t bytes() const { return size_ * sizeof(T); }

};

template<typename T>
struct device_memory : memory_holder<T> {
    device_memory(std::size_t num) : memory_holder<T>([num](){
        T* ptr = NULL;
        cudaMalloc(&ptr, num * sizeof(T));

        return std::unique_ptr<T, void(*)(T*)>{ptr, [](T* ptr) { cudaFree(ptr); }};
    }(), num) {}

    void from_host(T* hptr) {
        cudaMemcpy(this->data(), hptr, this->bytes(), cudaMemcpyHostToDevice);
    }

    void to_host(T* hptr) {
        cudaMemcpy(hptr, this->data(), this->bytes(), cudaMemcpyDeviceToHost);
    }
};

template<typename T>
struct shared_memory : memory_holder<T> {
    shared_memory(std::size_t num) : memory_holder<T>([num](){
        T* ptr = NULL;
        cudaMallocManaged(&ptr, num * sizeof(T));

        return std::unique_ptr<T, void(*)(T*)>{ptr, [](T* ptr) { cudaFree(ptr); }};
    }(), num) {}

    void advise(cudaMemoryAdvise mem_adv, int gpu_id) {
        cudaMemAdvise(this->data(), this->bytes(), mem_adv, gpu_id);
    }

    void prefetch_device(int gpu_id) {
        cudaMemPrefetchAsync(this->data(), this->bytes(), gpu_id);
    }

    void prefetch_host() {
        cudaMemPrefetchAsync(this->data(), this->bytes(), cudaCpuDeviceId);
    }
};

template<typename T>
struct pinned_memory : memory_holder<T> {
    pinned_memory(std::size_t num) : memory_holder<T>([num](){
        T* ptr = NULL;
        cudaMallocHost(&ptr, num * sizeof(T));

        return std::unique_ptr<T, void(*)(T*)>{ptr, [](T* ptr) { cudaFreeHost(ptr); }};
    }(), num) {}
};
