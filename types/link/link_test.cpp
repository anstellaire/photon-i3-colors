#include "link.hpp"

#include <array>
#include <iostream>
#include <numeric>

#define TEST_CASE(fname, rng)                                            \
    if(fname{}(rng.begin(), rng.end()) != true) {                        \
        std::cerr << "[TEST] > FAIL (" << #fname << ")" << std::endl;    \
    } else {                                                             \
        std::cerr << "[TEST] > pass (" << #fname << ")" << std::endl;    \
    }                                                                    \

namespace utils {

    template<typename I, typename F>
    bool check(I begin, I end, F f) {
        int i = 0;

        while (begin != end)
            if (*(begin++) != f(i++))
                return false;

        return true;
    }

    int decrease(int x) { return x - 1; }

} // namespace utils


struct test_pipeline_all_laziness {
    template<typename I>
    bool operator()(I begin, I end) {
        std::iota(begin, end, 0);

        enn::make_context(begin, end)
            | ([](int x){ return x*2; })
            | utils::decrease;

        return utils::check(begin, end, [](std::size_t i){ return i; });
    }
};

struct test_pipeline_all {
    template<typename I>
    bool operator()(I begin, I end) {
        std::iota(begin, end, 0);

        enn::make_context(begin, end)
            | ([](int x){ return x*2; })
            | utils::decrease
            | enn::execute;

        return utils::check(begin, end, [](std::size_t i){ return (i*2)-1; });
    }
};

struct test_pipeline_decomposed_laziness {
    template<typename I>
    bool operator()(I begin, I end) {
        std::iota(begin, end, 0);

        auto chain = enn::make_link()
            | [](int x){ return -1; };

        enn::make_context(begin, end)
            | chain
            | utils::decrease;

        return utils::check(begin, end, [](std::size_t i){ return i; });
    }
};

struct test_pipeline_decomposed {
    template<typename I>
    bool operator()(I begin, I end) {
        std::iota(begin, end, 0);

        auto chain = enn::make_link()
            | ([](int x){ return x*2; });

        enn::make_context(begin, end)
            | chain
            | utils::decrease
            | enn::execute;

        return utils::check(begin, end, [](std::size_t i){ return (i*2)-1; });
    }
};

int main() {
    std::array<int, 10> arr = {};

    TEST_CASE(test_pipeline_all_laziness, arr);
    TEST_CASE(test_pipeline_all, arr);
    TEST_CASE(test_pipeline_decomposed_laziness, arr);
    TEST_CASE(test_pipeline_decomposed, arr);
}
