#pragma once

#include <iterator>

namespace sweets {
namespace algs {
namespace serial {

    template<typename I>
    using val = typename std::iterator_traits<I>::value_type;

    template<typename I>
    using category = typename std::iterator_traits<I>::iterator_category;

    // -------------------------------------------------------------------------
    //   IMPLEMENTATION FOR RANDOM ACCESS ITERATORS
    // -------------------------------------------------------------------------

    template<typename I>
    I details_find_binary(I begin, I end, val<I> const& target, std::random_access_iterator_tag) {

        while (begin < end) {
            I middle = begin + (std::distance(begin, end) / 2);

            if (*middle == target)
                return middle;
            else if (*middle < target)
                begin = ++middle;
            else if (*middle > target)
                end = middle;
        }

        return end;
    }

    // -------------------------------------------------------------------------
    //   FALLBACK IMPLEMENTATION FOR OTHER ITERATORS
    // -------------------------------------------------------------------------

    template<typename I>
    I details_find_binary(I begin, I end, val<I> const& target, ...) {

        for(; begin != end; ++begin)
            if (*begin == target)
                return begin;

        return end;
    }

    // -------------------------------------------------------------------------
    //   DISPATCH
    // -------------------------------------------------------------------------

    template<typename I>
    I find_binary(I begin, I end, val<I> const& target) {
        return details_find_binary(begin, end, target, category<I>{});
    }

} // namespace serial
} // namespace algs
} // namespace sweets
