#ifndef ENN_CALLABLE_TRAITS_HPP
#define ENN_CALLABLE_TRAITS_HPP

#include <tuple>
#include <type_traits>

namespace enn {
namespace callable_details {
namespace utils {

    // helper types ------------------------------------------------------------

    template<typename Cls>
    class is_callable_object {

        template<typename>
        struct SFINAE {};

        template<typename T, typename Ret, typename... Args>
        struct SFINAE<Ret (T::*)(Args...)> {};

        template<typename T, typename Ret, typename... Args>
        struct SFINAE<Ret (T::*)(Args...) const> {};

        template<typename T>
        static char test(SFINAE<decltype(&T::operator())>*);

        template<typename T>
        static long test(...);

    public:

        static constexpr bool value = sizeof(test<Cls>(0)) == sizeof(char);

    };

    // info types --------------------------------------------------------------

    template<typename Ret, typename... Args>
    struct callable_info {
        using return_type = Ret;
        using arg_types = std::tuple<Args...>;

        static constexpr std::size_t arg_num = sizeof...(Args);

        template<std::size_t arg_idx>
        struct arg {
            using type = typename std::tuple_element<arg_idx, arg_types>::type;
        };
    };

    enum class callable_type {
        NONCALLABLE_OBJECT,
        CONST_CALLABLE_OBJECT,
        CALLABLE_OBJECT,
        CONST_METHOD_POINTER,
        METHOD_POINTER,
        FUNCTION_POINTER,
        FUNCTION
    };

    template<callable_type type_enum_value>
    struct callable_type_info {
        static constexpr callable_type type = type_enum_value;
        static constexpr bool is_callable =
            type_enum_value != callable_type::NONCALLABLE_OBJECT;
    };

    template<typename Cls>
    struct object_const_info {
        static constexpr bool is_object_constant = std::is_const<Cls>::value;
    };

    template<bool is_constant>
    struct method_const_info {
        static constexpr bool is_method_constant = is_constant;
    };

    template<bool is_pointer>
    struct pointer_info {
        static constexpr bool is_function_pointer = is_pointer;
    };

} // namespace utils

namespace dispatchers {

    // function_object_method_dispatcher ---------------------------------------

    template<typename>
    struct function_object_method_dispatcher;

    template<typename Ret, typename Cls, typename... Args>
    struct function_object_method_dispatcher<Ret (Cls::*)(Args...)> :
        utils::callable_type_info<utils::callable_type::CALLABLE_OBJECT>,
        utils::callable_info<Ret, Args...>,
        utils::method_const_info<false>
    {};

    template<typename Ret, typename Cls, typename... Args>
    struct function_object_method_dispatcher<Ret (Cls::*)(Args...) const> :
        utils::callable_type_info<utils::callable_type::CONST_CALLABLE_OBJECT>,
        utils::callable_info<Ret, Args...>,
        utils::method_const_info<true>
    {};

    // function_object_dispatcher ----------------------------------------------

    template<typename Cls, bool = utils::is_callable_object<Cls>::value>
    struct function_object_dispatcher;

    template<typename Cls>
    struct function_object_dispatcher<Cls, false> :
        utils::callable_type_info<utils::callable_type::NONCALLABLE_OBJECT>,
        utils::object_const_info<Cls>
    {};

    template<typename Cls>
    struct function_object_dispatcher<Cls, true> :
        function_object_method_dispatcher<decltype(&Cls::operator())>,
        utils::object_const_info<Cls>
    {};

    // function_dispatcher -----------------------------------------------------

    template<typename Cls>
    struct function_dispatcher :
        function_object_dispatcher<Cls>
    {};

    template<typename Ret, typename Cls, typename... Args>
    struct function_dispatcher<Ret (Cls::*)(Args...)> :
        utils::callable_type_info<utils::callable_type::METHOD_POINTER>,
        utils::callable_info<Ret, Cls, Args...>,
        utils::method_const_info<false>,
        utils::pointer_info<true>
    {};

    template<typename Ret, typename Cls, typename... Args>
    struct function_dispatcher<Ret (Cls::*)(Args...) const> :
        utils::callable_type_info<utils::callable_type::CONST_METHOD_POINTER>,
        utils::callable_info<Ret, Cls, Args...>,
        utils::method_const_info<true>,
        utils::pointer_info<true>
    {};

    template<typename Ret, typename... Args>
    struct function_dispatcher<Ret (*)(Args...)> :
        utils::callable_type_info<utils::callable_type::FUNCTION_POINTER>,
        utils::callable_info<Ret, Args...>,
        utils::pointer_info<true>
    {};

    template<typename Ret, typename... Args>
    struct function_dispatcher<Ret(Args...)> :
        utils::callable_type_info<utils::callable_type::FUNCTION>,
        utils::callable_info<Ret, Args...>,
        utils::pointer_info<false>
    {};

} // namespace dispatchers
} // namespace callable_details

template<typename T>
using callable_traits = callable_details::dispatchers::function_dispatcher<T>;

using callable_type = callable_details::utils::callable_type;

} // namespace enn

#endif // ENN_CALLABLE_TRAITS_HPP
