#pragma once

#include "heap_iterator.hpp"

#include <vector>
#include <functional>

namespace sweets {
namespace ds {

    template< typename T, typename Comp = std::greater<T>>
    class heap final {

        std::vector<T> _data;              // implemented using dynamic array
        constexpr static int ch_num = 2;    // number of children each node has

    public:

        using iterator       = heap_iterator<T, T&, T*>;
        using const_iterator = heap_iterator<T, T const&, T const*>;

        // ---------------------------------------------------------------------
        //   HEAP SPECIAL METHODS
        // ---------------------------------------------------------------------

        heap() = default;

        explicit heap(std::vector<T> data) : _data(std::move(data)) {
            iterator it = (begin() + _data.size() / 2 - 1);

            for (; it >= begin(); --it) siftdown(it);
        }

        void swap(heap& other) { _data.swap(other._data); }
        void clear() { _data.clear(); }

        bool empty() const { return _data.empty(); }
        size_t size()  const { return _data.size(); }

        // ---------------------------------------------------------------------
        //   HEAP ITERATOR GETTERS
        // ---------------------------------------------------------------------

        iterator       begin()       { return       iterator(_data.data()); }
        const_iterator begin() const { return const_iterator(_data.data()); }
        iterator       end()         { return       iterator(_data.data() + _data.size()); }
        const_iterator end()   const { return const_iterator(_data.data() + _data.size()); }

        // ---------------------------------------------------------------------
        //   HEAP API
        // ---------------------------------------------------------------------

        iterator       get_root()       { return begin(); }
        const_iterator get_root() const { return begin(); }

        void extract_root() {
            if (begin() == end()) return;

            std::swap(*begin(), *--end());
            _data.pop_back();

            siftdown(begin());
        }

        iterator insert(T value) {
            _data.push_back(std::move(value));

            return siftup(--end());
        }

        void remove(iterator it) {
            if (it < begin() || it >= end()) return;

            std::swap(*it, *--end());
            _data.pop_back();

            sift(it);
        }

        iterator change_priority(iterator it, T value) {
            if (it < begin() || it >= end()) return end();

            *it = std::move(value);

            return sift(it);
        }

    private:

        // ---------------------------------------------------------------------
        //   HEAP NODE NAVIGATION METHODS
        // ---------------------------------------------------------------------

        ptrdiff_t index(iterator it) {
            return it - begin();
        }

        iterator parent(iterator it) {
            ptrdiff_t i = index(it) > 0 ? index(it) : 0;

            return iterator(_data.data() + (i - 1) / ch_num);
        }

        iterator left_child(iterator it) {
            ptrdiff_t i = index(it) > 0 ? index(it) : 0;

            iterator tmp(_data.data() + i * ch_num + 1);

            return tmp < end() ? tmp : end();
        }

        iterator right_child(iterator it) {
            ptrdiff_t i = index(it) > 0 ? index(it) : 0;

            iterator tmp(_data.data() + i * ch_num + 2);

            return tmp < end() ? tmp : end();
        }

        // ---------------------------------------------------------------------
        //   HEAP REPAIR METHODS
        // ---------------------------------------------------------------------

        iterator sift(iterator it) {
            if (it < begin() || it >= end())
                return end();

            if (Comp{}(*it, *parent(it)))
                return siftup(it);

            if ( (left_child(it)  != end() && Comp{}( *left_child(it),  *it )) ||
                (right_child(it) != end() && Comp{}( *right_child(it), *it )) )
                return siftdown(it);

            return it;
        }

        iterator siftup(iterator it) {
            if (it < begin() || it >= end()) return end();

            while ( (index(it) > 0) && (Comp{}(*it, *parent(it))) ) {
                std::swap(*parent(it), *it);
                it = parent(it);
            }

            return it;
        }

        iterator siftdown(iterator it) {
            if (it < begin() || it >= end()) return end();

            while (true) {
                iterator higher_prior_it = it;

                iterator l = left_child(it);
                if (l != end() && Comp{}(*l, *higher_prior_it)) higher_prior_it = l;

                iterator r = right_child(it);
                if (r != end() && Comp{}(*r, *higher_prior_it)) higher_prior_it = r;

                if (it == higher_prior_it) return higher_prior_it;

                std::swap(*it, *higher_prior_it);
                it = higher_prior_it;
            }
        }

    };

} // namespace algs
} // namespace sweets
