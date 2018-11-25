#include "heap.hpp"

#include <iostream>

int main() {

    std::vector<int> vec({0,13,1,12,2,11,3,10,4,9,5,8,6,7});

    std::cout << "Initial vector: " << std::endl;
    for (int i : vec)
        std::cout << i << " ";
    std::cout << std::endl << std::endl;

    // min-heap: heap<T, std::less<T>>
    // max-heap: heap<T, std::greater<T>> or just heap<T>
    sweets::ds::heap<int> heap(std::move(vec));

    // just iterate over heap
    std::cout << "Heap (presented as a vector): " << std::endl;
    for (int i : heap)
        std::cout << i << " ";
    std::cout << std::endl << std::endl;

    // extract heap root (sorted)
    std::cout << "Heap: " << std::endl;
    for ( ; !heap.empty() ; ) {
        std::cout << *heap.get_root() << " ";
        heap.extract_root();
    }
    std::cout << std::endl << std::endl;

}
