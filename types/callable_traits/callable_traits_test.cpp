#include "callable_traits.hpp"

namespace test {

    struct object_const_callable {
        float operator()(int value) const {
            return value;
        }
    };

    struct object_callable {
        float operator()(int value) {
            return value;
        }
    };

    struct object_noncallable {
        static float method_static(int value) {
            return value;
        }

        float method_const(int value) const {
            return value;
        }

        float method(int value) {
            return value;
        }
    };

    float function(int value) {
        return value;
    }

    template<typename T, enn::callable_type expected>
    void check() {
        static_assert(enn::callable_traits<T>::type == expected, "FAIL");
    };

} // namespace test

int main() {

    auto lambda = [](int x) -> float { return x; };
    auto lambda_mut = [](int x) mutable -> float { return x; };

    test::check<
        decltype(&test::object_noncallable::method_const),
        enn::callable_type::CONST_METHOD_POINTER>();
    test::check<
        decltype(&test::object_noncallable::method),
        enn::callable_type::METHOD_POINTER>();

    test::check<
        decltype(&test::object_noncallable::method_static),
        enn::callable_type::FUNCTION_POINTER>();
    test::check<
        decltype(test::object_noncallable::method_static),
        enn::callable_type::FUNCTION>();

    test::check<
        decltype(&test::function),
        enn::callable_type::FUNCTION_POINTER>();
    test::check<
        decltype(test::function),
        enn::callable_type::FUNCTION>();

    test::check<
        decltype(lambda),
        enn::callable_type::CONST_CALLABLE_OBJECT>();
    test::check<
        decltype(lambda_mut),
        enn::callable_type::CALLABLE_OBJECT>();
    test::check<
        test::object_const_callable,
        enn::callable_type::CONST_CALLABLE_OBJECT>();
    test::check<
        test::object_callable,
        enn::callable_type::CALLABLE_OBJECT>();
    test::check<
        test::object_noncallable,
        enn::callable_type::NONCALLABLE_OBJECT>();

}
