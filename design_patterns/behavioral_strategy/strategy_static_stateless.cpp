#include <iostream>

// -----------------------------------------------------------------------------
//   PATTERN (STATELESS)
// -----------------------------------------------------------------------------

struct stateless_strategy_one {
    static std::string name() { return "stateless_strategy_one"; }
};

struct stateless_strategy_two {
    static std::string name() { return "stateless_strategy_two"; }
};

template<typename Strategy>
struct stateless_context {
    static std::string call() {
        return "stateless_context::call(" + Strategy::name() + ")";
    }
};

template<typename Strategy>
std::string call() {
    return "call(" + Strategy::name() + ")";
}

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {

    std::cout << stateless_context<stateless_strategy_one>::call() << std::endl;
    std::cout << stateless_context<stateless_strategy_two>::call() << std::endl;

    std::cout << call<stateless_strategy_one>() << std::endl;
    std::cout << call<stateless_strategy_two>() << std::endl;

}
