#include "sort_quick.hpp"

#include <vector>
#include <iostream>

int main() {

    std::vector<int> vec = {4, 5, 3, 6, 3, 9, 4, 2, 7, 3, 1, 8, 0, 9};

    std::cout << "Initial vector: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    sweets::algs::serial::sort_quick(vec.begin(), vec.end());

    std::cout << "Sorted vector:  ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

}
