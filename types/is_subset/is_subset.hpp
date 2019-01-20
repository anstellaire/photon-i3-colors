#ifndef ENN_IS_SUBSET_HPP
#define ENN_IS_SUBSET_HPP

namespace enn {

    template<typename ISub, typename ISrc, typename F>
    inline bool is_subset(
        ISub sub_begin, ISub sub_end, ISrc src_begin, ISrc src_end, F equals) {

        for (; sub_begin != sub_end; ++sub_begin) {
            bool found = false;

            for (ISrc newbegin = src_begin; newbegin != src_end; ++newbegin) {
                if (equals(*sub_begin, *newbegin)) {
                    found = true;
                    break;
                }
            }

            if (!found)
                return false;
        }

        return true;
    }

    template<typename RSub, typename RSrc, typename F>
    inline bool is_subset(RSub sub, RSrc src, F equals) {
        return contains(sub.begin(), sub.end(), src.begin(), src.end(), equals);
    }

} // namespace enn

#endif // ENN_IS_SUBSET_HPP
