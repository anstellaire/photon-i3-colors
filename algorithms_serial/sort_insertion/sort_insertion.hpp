#pragma once

#include <iterator>
#include <functional>

namespace sweets {
namespace algs {
namespace serial {

    template<typename I>
    using val = typename std::iterator_traits<I>::value_type;

    // -------------------------------------------------------------------------
    //   IMPLEMENTATION
    // -------------------------------------------------------------------------

    template<typename Iterator, typename Comparator>
    void sort_insertion(Iterator begin, Iterator end, Comparator compare) {
        for (Iterator i = std::next(begin); i != end; ++i) {
            Iterator j = i;

            while ( j != begin && compare(*j, *std::prev(j)) ) {
                std::iter_swap(j, std::prev(j));
                --j;
            }
        }
    }

    template<typename Iterator>
    void sort_insertion(Iterator begin, Iterator end) {
        sort_insertion(begin, end, std::less<val<Iterator>>());
    }

} // namespace serial
} // namespace algs
} // namespace sweets
