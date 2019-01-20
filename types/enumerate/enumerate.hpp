#ifndef ENN_ENUMERATE_HPP
#define ENN_ENUMERATE_HPP

#include <cstddef>
#include <iterator>

namespace enn {

    // enumerate_iterator_element ----------------------------------------------

    template<typename Id, typename It>
    struct enumerate_iterator_element {
        Id id;
        typename std::iterator_traits<It>::reference value;
    };

    // enumerate_iterator ------------------------------------------------------

    template<typename Id, typename It>
    class enumerate_iterator {

        Id idx_;
        It iter_;

    public:

        enumerate_iterator(Id idx, It iter) :
            idx_(idx), iter_(iter) {}

        enumerate_iterator_element<Id, It> operator*() {
            return enumerate_iterator_element<Id, It>{idx_, *iter_};
        }

        enumerate_iterator<Id, It> operator++() {
            return enumerate_iterator<Id, It>{idx_++, iter_++};
        }

        bool operator!=(enumerate_iterator<Id, It> other) {
            return iter_ != other.iter_;
        }

    };

    // enumerate_range ---------------------------------------------------------

    template<typename Id, typename It>
    class enumerate_range {

        It begin_, end_;
        Id idx_;

    public:

        enumerate_range(It begin, It end, Id idx) :
            begin_(begin), end_(end), idx_(idx) {}

        enumerate_iterator<Id, It> begin() {
            return enumerate_iterator<Id, It>{idx_, begin_};
        }

        enumerate_iterator<Id, It> end() {
            return enumerate_iterator<Id, It>{idx_, end_};
        }

    };

    // enumerate helpers -------------------------------------------------------

    template<typename Id = std::size_t, typename It>
    inline auto enumerate(It begin, It end, Id idx = 0)
        -> decltype(enumerate_range<Id, It>{begin, end, idx}) {

        return enumerate_range<Id, It>{begin, end, idx};
    }

    template<typename Id = std::size_t, typename Rng>
    inline auto enumerate(Rng&& rng, Id idx = 0)
        -> decltype(enumerate_range<Id, decltype(rng.begin())>{rng.begin(), rng.end(), idx}) {

        return enumerate_range<Id, decltype(rng.begin())>{rng.begin(), rng.end(), idx};
    }

} // namespace enn

#endif // ENN_ENUMERATE_HPP
