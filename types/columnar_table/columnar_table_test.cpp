#include "columnar_table.hpp"

#include <iostream>
#include <string>

int main() {
    enn::columnar_table<int, std::string> t{};

    std::tuple<int, std::string> fields1(1, "lalala");
    std::tuple<int, std::string> fields2(2, "blabla");

    t.push_row(fields1);
    t.push_row(fields2);

    auto g1 = t.get_row(0);
    auto g2 = t.get_row(1);

    std::cout << std::get<0>(g1) << ", " << std::get<1>(g1) << std::endl;
    std::cout << std::get<0>(g2) << ", " << std::get<1>(g2) << std::endl;
}
