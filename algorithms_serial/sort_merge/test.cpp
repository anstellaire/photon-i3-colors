#include "sort_merge.hpp"

#include <vector>
#include <iostream>

int main() {

    std::vector<int> vec = {0, 9, 1, 8, 2, 7, 3, 6, 4, 5};

    std::cout << "Initial vector: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    sweets::algs::serial::sort_merge(vec.begin(), vec.end());

    std::cout << "Sorted vector:  ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

}
