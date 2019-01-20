#include "sequence.hpp"

#include <iostream>

int main() {
    for (auto i : enn::sequence(0, 33, 1))
        std::cout << i << " ";
    std::cout << std::endl;
    for (auto i : enn::sequence(0, 33, 5))
        std::cout << i << " ";
    std::cout << std::endl;
    for (auto i : enn::sequence(33, 0, -1))
        std::cout << i << " ";
    std::cout << std::endl;
    for (auto i : enn::sequence(33, 0, -5))
        std::cout << i << " ";
    std::cout << std::endl;
}
