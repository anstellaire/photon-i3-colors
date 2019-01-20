#ifndef ENN_SEQUENCE_HPP
#define ENN_SEQUENCE_HPP

namespace enn {

    // sequence_iterator -------------------------------------------------------

    template<typename Int>
    class sequence_iterator {

        Int idx_, step_;

    public:

        sequence_iterator(Int idx, Int step) :
            idx_(idx), step_(step) {}

        Int operator*() {
            return idx_;
        }

        Int operator++() {
            Int tmp = idx_;
            idx_ += step_;
            return tmp;
        }

        bool operator!=(sequence_iterator other) {
            return (step_ > 0 && idx_ < other.idx_) || (step_ < 0 && idx_ > other.idx_);
        }

    };

    // sequence_range ----------------------------------------------------------

    template<typename Int>
    class sequence_range {

        Int begin_, end_, step_;

    public:

        sequence_range(Int begin, Int end, Int step) :
            begin_(begin), end_(end), step_(step) {}

        sequence_iterator<Int> begin() {
            return sequence_iterator<Int>{begin_, step_};
        }

        sequence_iterator<Int> end() {
            return sequence_iterator<Int>{end_, step_};
        }

    };

    // sequence helper ---------------------------------------------------------

    template<typename Int>
    inline sequence_range<Int> sequence(Int start, Int stop, Int step = 1) {
        return sequence_range<Int>(start, stop, step);
    }

} // namespace enn

#endif // ENN_SEQUENCE_HPP
