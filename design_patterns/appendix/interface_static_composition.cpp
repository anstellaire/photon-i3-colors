#include <iostream>

// -----------------------------------------------------------------------------
//   INTERFACE (static polymorphism + composition)
// -----------------------------------------------------------------------------

template<typename Impl>
struct base {
    Impl impl;

    static char const* name_impl() {
        return "default implementation";
    }

    char const* name() {
        return impl.name_impl();
    }
};

struct derived1 {
    char const* name_impl() {
        return "derived1 implementation";
    }
};

struct derived2 {
    char const* name_impl() {
        return base<derived2>::name_impl();
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

template<typename Impl>
void print_name(base<Impl> p) {
    std::cout << p.name() << std::endl;
}

int main() {
    print_name(base<derived1>{});
    print_name(base<derived2>{});
}
