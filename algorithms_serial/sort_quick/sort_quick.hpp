#pragma once

#include <iterator>
#include <functional>

namespace sweets {
namespace algs {
namespace serial {

    template<typename I>
    using val = typename std::iterator_traits<I>::value_type;

    // -------------------------------------------------------------------------
    //   PARTITION ON <=X, X, >X
    // -------------------------------------------------------------------------

    template<typename Iterator, typename Comparator>
    Iterator partition(Iterator begin, Iterator end, Comparator compare) {

        Iterator j = begin;

        for (Iterator i = std::next(begin); i != end; ++i)
            if (compare(*i, *begin))
                std::iter_swap(i, ++j);

        std::iter_swap(begin, j);

        return j;
    }

    // -------------------------------------------------------------------------
    //   QUICK SORT IMPLEMENTATION
    // -------------------------------------------------------------------------

    template<typename Iterator, typename Comparator>
    void sort_quick(Iterator begin, Iterator end, Comparator compare) {
        if (std::distance(begin, end) < 2) return;

        Iterator middle = partition(begin, end, compare);

        sort_quick(begin, middle, compare);
        sort_quick(++middle, end, compare);
    }

    template<typename Iterator>
    void sort_quick(Iterator begin, Iterator end) {
        sort_quick(begin, end, std::less<val<Iterator>>());
    }

} // namespace serial
} // namespace algs
} // namespace sweets
