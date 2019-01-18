#ifndef ENN_SETTER_HPP
#define ENN_SETTER_HPP

#include <type_traits>
#include <utility>

namespace enn {
    template<typename T>
    using setter_dec = typename std::decay<T>::type;
} // namespace enn

#define ENN_GEN_SET(fn_name, fd_name)                                          \
    auto fn_name(enn::setter_dec<decltype(fd_name)> val) -> decltype(*this) {  \
        fd_name = std::move(val);                                              \
        return *this;                                                          \
    }                                                                          \

#define ENN_GEN_GET_VAL(fn_name, fd_name)                                      \
    auto fn_name() -> enn::setter_dec<decltype(fd_name)> {                     \
        return fd_name;                                                        \
    }                                                                          \

#define ENN_GEN_GET_VAL_CONST(fn_name, fd_name)                                \
    auto fn_name() const -> enn::setter_dec<decltype(fd_name)> {               \
        return fd_name;                                                        \
    }                                                                          \

#define ENN_GEN_GET_REF(fn_name, fd_name)                                      \
    auto fn_name() -> enn::setter_dec<decltype(fd_name)>& {                    \
        return fd_name;                                                        \
    }                                                                          \

#define ENN_GEN_GET_REF_CONST(fn_name, fd_name)                                \
    auto fn_name() const -> enn::setter_dec<decltype(fd_name)> const& {        \
        return fd_name;                                                        \
    }                                                                          \


#endif // ENN_SETTER_HPP
