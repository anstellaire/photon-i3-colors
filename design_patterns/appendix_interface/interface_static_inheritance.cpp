#include <iostream>

// -----------------------------------------------------------------------------
//   INTERFACE (static polymorphism + inheritance)
// -----------------------------------------------------------------------------

template<typename Impl>
struct base {
    // unlike CRTP, it helps avoid UB for methods manipulating Impl state when
    // accepting `base` by copy, since Impl state is lost during object slicing
    Impl* impl;

    char const* name_impl() {
        return "default implementation";
    }

    char const* name() {
        return impl->name_impl();
    }
};

struct derived1 : base<derived1> {
    derived1() : base<derived1>{this} {}

    char const* name_impl() {
        return "derived1 implementation";
    }
};

struct derived2 : base<derived2> {
    derived2() : base<derived2>{this} {}
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

template<typename Impl>
void print_name(base<Impl> p) {
    std::cout << p.name() << std::endl;
}

int main() {
    print_name(derived1{});
    print_name(derived2{});
}
