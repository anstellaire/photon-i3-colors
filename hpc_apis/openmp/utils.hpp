#pragma once

#include <cstddef>
#include <random>
#include <memory>
#include <omp.h>

namespace sweets {
namespace hpc {
namespace openmp {
namespace utils {

    template<typename T>
    class mat_view {

        T* mat_;
        std::size_t rows_, cols_, base_cols_;

        mat_view(T* mat, std::size_t rows, std::size_t cols, std::size_t base_cols) :
            mat_(mat), rows_(rows), cols_(cols), base_cols_(base_cols) {}

    public:

        mat_view(T* mat, std::size_t rows, std::size_t cols) :
            mat_view(mat, rows, cols, cols) {}

        std::size_t rows() const { return rows_; }
        std::size_t cols() const { return cols_; }

        T const* operator[](std::size_t idx) const { return mat_ + base_cols_ * idx; }
        T* operator[](std::size_t idx) { return mat_ + base_cols_ * idx; }

        mat_view<T> tile(std::size_t row_idx, std::size_t col_idx, std::size_t tile_size) {
            return mat_view<T>(mat_ + base_cols_ * row_idx + col_idx, tile_size, tile_size, base_cols_);
        }
    };

    template<typename V, unsigned long lower, unsigned long upper>
    struct random_generator {
        void operator()(V& val) {
            static std::random_device dev;
            static std::mt19937 eng(dev());
            static std::uniform_int_distribution<std::mt19937::result_type> dst(lower, upper);

            val = static_cast<V>(dst(eng));
        }
    };

    template<typename T>
    std::unique_ptr<T[]> get_sequence(std::size_t mat_size) {
        return std::unique_ptr<T[]>{new T[mat_size]};
    }

    template<typename I, typename F>
    void for_each(I begin, I end, F f) {
        for (; begin != end; ++begin)
            f(*begin);
    }

    template<typename F>
    double measure(F f) {
        double start = omp_get_wtime();
        f();
        return omp_get_wtime() - start;
    };

} // namespace utils
} // namespace openmp
} // namespace hpc
} // namespace sweets
