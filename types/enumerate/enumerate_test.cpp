#include "enumerate.hpp"

#include <array>
#include <iostream>

int main() {
    std::array<char, 10> arr = {'a','b','c','d','e','f','g','h','i','j'};

    for (auto i : enn::enumerate(arr))
        std::cout << "(" << i.id << "," << i.value << ") ";
    std::cout << std::endl << std::endl;
    for (auto i : enn::enumerate(arr, 10))
        std::cout << "(" << i.id << "," << i.value << ") ";
    std::cout << std::endl << std::endl;
    for (auto i : enn::enumerate(arr.begin(), arr.end()))
        std::cout << "(" << i.id << "," << i.value << ") ";
    std::cout << std::endl << std::endl;
    for (auto i : enn::enumerate(arr.begin(), arr.end(), 10))
        std::cout << "(" << i.id << "," << i.value << ") ";
    std::cout << std::endl << std::endl;
}
