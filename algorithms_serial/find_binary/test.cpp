#include "find_binary.hpp"

#include <vector>
#include <iostream>

int main() {

    std::vector<int> v = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

    auto it = sweets::algs::serial::find_binary(v.begin(), v.end(), 8);

    if (it != v.end())
        std::cout << *it << std::endl;
    else
        std::cout << "NOT FOUND" << std::endl;

}
