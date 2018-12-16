#include <iostream>
#include <memory>

// -----------------------------------------------------------------------------
//   INTERFACE (dynamic polymorphism)
// -----------------------------------------------------------------------------

struct base {
    virtual ~base() {}

    virtual char const* name() {
        return "default implementation";
    }
};

struct derived1 : base {
    char const* name() {
        return "derived1 implementation";
    }
};

struct derived2 : base {};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

void print_name(base& p) {
    std::cout << p.name() << std::endl;
}

int main() {
    print_name(*std::unique_ptr<derived1>(new derived1));
    print_name(*std::unique_ptr<derived2>(new derived2));
}
