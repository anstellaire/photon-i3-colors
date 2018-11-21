#pragma once

#include <iterator>
#include <vector>
#include <functional>

namespace sweets {
namespace algs {
namespace serial {

    template<typename I>
    using val = typename std::iterator_traits<I>::value_type;

    // -------------------------------------------------------------------------
    //   MERGE IMPLEMENTATION
    // -------------------------------------------------------------------------

    template<typename In, typename Out, typename C>
    Out merge(In begin1, In end1, In begin2, In end2, Out begin_out, C compare) {

        for (; begin1 != end1; ++begin_out) {
            if (begin2 == end2)
                return std::copy(begin1, end1, begin_out);

            if (compare(*begin2, *begin1)) {
                *begin_out = *begin2;
                ++begin2;
            } else {
                *begin_out = *begin1;
                ++begin1;
            }
        }

        return std::copy(begin2, end2, begin_out);
    }

    // -------------------------------------------------------------------------
    //   MERGE SORT IMPLEMENTATION
    // -------------------------------------------------------------------------

    template<typename Iterator, typename Comparator>
    void sort_merge(Iterator begin, Iterator end, Comparator compare) {
        auto sequence_size = std::distance(begin, end);

        if (sequence_size > 1) {

            // get the middle
            Iterator middle = begin;
            std::advance(middle, sequence_size / 2);

            // recursive call
            sort_merge(begin, middle, compare);
            sort_merge(middle, end, compare);

            // merge with temp memory
            std::vector<val<Iterator>> tmp;
            tmp.reserve(sequence_size);

            // merge two sorted sub-sequences
            merge(begin, middle, middle, end, std::back_inserter(tmp), compare);

            // copy to initial container
            std::copy(tmp.begin(), tmp.end(), begin);
        }
    }

    template<typename Iterator>
    void sort_merge(Iterator begin, Iterator end) {
        sort_merge(begin, end, std::less<val<Iterator>>());
    }

} // namespace serial
} // namespace algs
} // namespace sweets
