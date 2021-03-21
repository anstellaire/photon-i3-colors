#include "mat_mult.hpp"

#include <cstddef>
#include <iostream>

using namespace sweets::hpc::openmp;

using test_type = int;
static const std::size_t mat_size = 1024;

int main() {

    // memory
    auto in1 = utils::get_sequence<test_type>(mat_size*mat_size);
    auto in2 = utils::get_sequence<test_type>(mat_size*mat_size);
    auto out_ser = utils::get_sequence<test_type>(mat_size*mat_size);
    auto out_par = utils::get_sequence<test_type>(mat_size*mat_size);

    // generator
    utils::random_generator<test_type, 0, 10> gen;
    auto zeroer = [](test_type& val){ val = 0; };

    // initialize
    utils::for_each(in1.get(), in1.get() + mat_size*mat_size, gen);
    utils::for_each(in2.get(), in2.get() + mat_size*mat_size, gen);
    utils::for_each(out_par.get(), out_par.get() + mat_size*mat_size, zeroer);
    utils::for_each(out_ser.get(), out_ser.get() + mat_size*mat_size, zeroer);

    // mat view
    utils::mat_view<test_type> in1_view(in1.get(), mat_size, mat_size);
    utils::mat_view<test_type> in2_view(in2.get(), mat_size, mat_size);
    utils::mat_view<test_type> out_ser_view(out_ser.get(), mat_size, mat_size);
    utils::mat_view<test_type> out_par_view(out_par.get(), mat_size, mat_size);

    // run serial
    double time_ser = utils::measure([&in1_view, &in2_view, &out_ser_view](){
        alg::mat_mult_serial_naive{}(in1_view, in2_view, out_ser_view);
    });

    // run parallel
    double time_par = utils::measure([&in1_view, &in2_view, &out_par_view](){
        alg::mat_mult_parallel{}(in1_view, in2_view, out_par_view);
    });

    // results
    std::cout << "Serial/Parallel Time: " << time_ser / time_par << std::endl;

    for (std::size_t i = 0; i < mat_size*mat_size; ++i) {
        if (out_ser.get()[i] != out_par.get()[i]) {
            std::cout << "Validation failure" << std::endl;
            break;
        }
    }

}
