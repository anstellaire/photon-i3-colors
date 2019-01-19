#ifndef ENN_TYPELIST_HPP
#define ENN_TYPELIST_HPP

namespace enn {

    // -------------------------------------------------------------------------
    //   TYPE LIST
    // -------------------------------------------------------------------------

    template<typename...>
    struct type_list;

    template<typename Head, typename... Rest>
    struct type_list<Head, Rest...> {
        using head = Head;
        using tail = type_list<Rest...>;
    };

    template<>
    struct type_list<> {};

    // -------------------------------------------------------------------------
    //   TYPE LIST LENGTH
    // -------------------------------------------------------------------------

    template<typename>
    struct type_list_length;

    template<typename Head, typename... Rest>
    struct type_list_length<type_list<Head, Rest...>> {
        static const unsigned length = 1 + type_list_length<Rest...>::length;
    };

    template<>
    struct type_list_length<type_list<>> {
        static const unsigned length = 0;
    };

    // -------------------------------------------------------------------------
    //   TYPE LIST MERGE
    // -------------------------------------------------------------------------

    template<typename, typename>
    struct type_list_merge;

    template<typename... LTypes, typename... RTypes>
    struct type_list_merge<type_list<LTypes...>, type_list<RTypes...>> {
        using type = type_list<LTypes..., RTypes...>;
    };

    // -------------------------------------------------------------------------
    //   TYPE LIST PUSH FRONT
    // -------------------------------------------------------------------------

    template<typename, typename>
    struct type_list_push_front;

    template<typename TNew, typename... TOld>
    struct type_list_push_front<TNew, type_list<TOld...>> {
        using type = type_list<TNew, TOld...>;
    };

    template<typename, typename>
    struct type_list_push_back;

    template<typename TNew, typename... TOld>
    struct type_list_push_back<TNew, type_list<TOld...>> {
        using type = type_list<TOld..., TNew>;
    };

    // -------------------------------------------------------------------------
    //   TYPE LIST POP FRONT
    // -------------------------------------------------------------------------

    template<typename>
    struct type_list_pop_front;

    template<typename Head, typename... Rest>
    struct type_list_pop_front<type_list<Head, Rest...>> {
        using type = type_list<Rest...>;
    };

} // namespace enn

#endif // ENN_TYPELIST_HPP
