#ifndef ENN_LINK_HPP
#define ENN_LINK_HPP

#include <utility> // std::forward

namespace enn {

    // -------------------------------------------------------------------------
    //   LINK
    // -------------------------------------------------------------------------

    template<typename FPrev, typename FCur>
    class link {

        FPrev fprev;
        FCur fcur;

    public:

        link(FPrev fprev, FCur fcur) :
            fprev(std::move(fprev)), fcur(std::move(fcur)) {}

        template<typename FNext>
        link<link<FPrev, FCur>, FNext> operator|(FNext fnext) {
            return link<link<FPrev, FCur>, FNext>{*this, std::move(fnext) };
        };

        template<typename V>
        auto operator()(V&& value)
            -> decltype(fcur(fprev(std::forward<V>(value)))) {

            return fcur(fprev(std::forward<V>(value)));
        }

    };

    template<typename FCur>
    class link<void, FCur> {

        FCur fcur;

    public:

        link(FCur fcur) :
            fcur(std::move(fcur)) {}

        template<typename FNext>
        link<FCur, FNext> operator|(FNext fnext) {
            return link<FCur, FNext>{this->fcur, std::move(fnext) };
        };

        template<typename V>
        auto operator()(V&& value)
            -> decltype(fcur(std::forward<V>(value))) {

            return fcur(std::forward<V>(value));
        }

    };

    template<>
    class link<void, void> {

    public:

        template<typename FNext>
        link<void, FNext> operator|(FNext fnext) {
            return link<void, FNext>{fnext};
        };

    };

    inline link<void, void> make_link() {
        return link<void, void>{};
    }

    // -------------------------------------------------------------------------
    //   CONTEXT
    // -------------------------------------------------------------------------

    static struct execute_type{} execute;

    template<typename F, typename I>
    class context {

        F func_;
        I begin_;
        I end_;

    public:

        context(F func, I begin, I end) :
            func_(func), begin_(begin), end_(end) {}

        void operator|(execute_type) {
            for (I it = begin_; it != end_; ++it)
                *it = func_(*it);
        }

        template<typename Fn>
        auto operator|(Fn fnext)
            -> decltype(make_context(func_ | fnext, begin_, end_)) {

            return make_context(func_ | fnext, begin_, end_);
        }

    };

    template<typename F, typename I>
    inline context<F, I> make_context(F func, I begin, I end) {
        return context<F, I>{func, begin, end};
    }

    template<typename I>
    inline auto make_context(I begin, I end)
        -> decltype(make_context(make_link(), begin, end)) {

        return make_context(make_link(), begin, end);
    }

} // namespace enn

#endif // ENN_LINK_HPP
