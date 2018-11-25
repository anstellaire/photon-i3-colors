#pragma once

#include "utils.hpp"

#include <cstddef>
#include <cassert>

namespace sweets {
namespace hpc {
namespace openmp {
namespace alg {

    using utils::mat_view;

    struct dotproduct_serial_naive {

        template<typename T>
        // __attribute__((optimize("no-tree-vectorize"))) // gcc
        void operator()(mat_view<T> const in1, mat_view<T> const in2, mat_view<T> out) {
            assert(in1.cols() == in2.rows());

            // #pragma novector // icc
            // #pragma loop(no_vector) // msvc
            // #pragma clang loop vectorize(disable) // clang
            for (std::size_t i = 0; i < in1.rows(); ++i) {
                // #pragma novector // icc
                // #pragma loop(no_vector) // msvc
                // #pragma clang loop vectorize(disable) // clang
                for (std::size_t j = 0; j < in2.cols(); ++j) {
                    out[i][j] = 0;

                    // #pragma novector // icc
                    // #pragma loop(no_vector) // msvc
                    // #pragma clang loop vectorize(disable) // clang
                    for (std::size_t k = 0; k < in1.cols(); ++k) {
                        out[i][j] += in1[i][k] * in2[k][j];
                    }
                }
            }
        }

    };

    struct dotproduct_parallel {

        template<typename T>
        void process_tile(mat_view<T> const tile1, mat_view<T> const tile2, mat_view<T> out) {
            for (std::size_t i = 0; i < tile1.rows(); ++i) {
                for(std::size_t j = 0; j < tile2.cols(); ++j) {
                    // #pragma ivdep
                    for (std::size_t k = 0; k < tile1.cols(); ++k) {
                        out[i][k] += tile1[i][j] * tile2[j][k];
                    }
                }
            }
        }

        template<typename T>
        void operator()(mat_view<T> in1, mat_view<T> in2, mat_view<T> out) {
            assert(in1.cols() == in2.rows());

            const std::size_t tile_size = 128;

            #pragma omp parallel for collapse(2)
            for (std::size_t i = 0; i < in1.rows(); i += tile_size) {
                for (std::size_t j = 0; j < in2.cols(); j += tile_size) {
                    for (std::size_t k = 0; k < in1.cols(); k += tile_size) {
                        process_tile(
                            in1.tile(i, k, tile_size),
                            in2.tile(k, j, tile_size),
                            out.tile(i, j, tile_size)
                        );
                    }
                }
            }
        }

    };

} // namespace alg
} // namespace openmp
} // namespace hpc
} // namespace sweets
