#pragma once

#include <iterator>
#include <cstdint>

namespace sweets {
namespace ds {

    template<typename VType, typename VRef, typename VPtr>
    class heap_iterator final {

        VType* _ptr;

    public:

        // ---------------------------------------------------------------------
        //   TYPEDEFS
        // ---------------------------------------------------------------------

        using iterator_type      = heap_iterator<VType, VRef, VPtr>;
        using iterator_category  = std::random_access_iterator_tag;

        using difference_type    = ptrdiff_t;

        using value_type         = VType;
        using reference          = VRef;
        using pointer            = VPtr;

        // ---------------------------------------------------------------------
        //   METHODS
        // ---------------------------------------------------------------------

        explicit heap_iterator(pointer ptr) : _ptr(ptr) {}

        reference      operator*  ()             { return *_ptr; }
        pointer        operator-> ()             { return  _ptr; }

        iterator_type& operator++ ()             { ++_ptr; return *this; }
        iterator_type& operator-- ()             { --_ptr; return *this; }
        iterator_type  operator++ (int)          { return iterator_type(_ptr++); }
        iterator_type  operator-- (int)          { return iterator_type(_ptr--); }

        iterator_type& operator+= (size_t index) { _ptr += index; return *this; }
        iterator_type& operator-= (size_t index) { _ptr -= index; return *this; }

        // ---------------------------------------------------------------------
        //   FRIEND OPERATORS
        // ---------------------------------------------------------------------

        friend iterator_type   operator+ (iterator_type const& it, size_t index) {
            return iterator_type(it) += index;
        }

        friend iterator_type   operator+ (size_t index, iterator_type const& it) {
            return iterator_type(it) += index;
        }

        friend iterator_type   operator- (iterator_type const& it, size_t index) {
            return iterator_type(it) -= index;
        }

        friend difference_type operator- (iterator_type const& it1, iterator_type const& it2) {
            return it1._ptr - it2._ptr;
        }

        friend bool operator<  (iterator_type const& it1, iterator_type const& it2) {
            return it1._ptr <  it2._ptr;
        }

        friend bool operator>  (iterator_type const& it1, iterator_type const& it2) {
            return it2 < it1;
        }

        friend bool operator<= (iterator_type const& it1, iterator_type const& it2) {
            return !(it2 < it1);
        }

        friend bool operator>= (iterator_type const& it1, iterator_type const& it2) {
            return !(it1 < it2);
        }

        friend bool operator== (iterator_type const& it1, iterator_type const& it2) {
            return !(it1 < it2 || it2 < it1);
        }

        friend bool operator!= (iterator_type const& it1, iterator_type const& it2) {
            return !(it1 == it2);
        }

    };

} // namespace ds
} // namespace sweets
