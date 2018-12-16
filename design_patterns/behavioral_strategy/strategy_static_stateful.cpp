#include <iostream>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

struct stateful_strategy_one {
    std::string state = "stateful_strategy_one";

    std::string operator()() { return state += "++"; }
};

struct stateful_strategy_two {
    std::string state = "stateful_strategy_two";

    std::string operator()() { return state += "##"; }
};

template<typename Strategy>
struct stateful_context {
    Strategy strategy;

    std::string call() {
        return "stateful_context::call(" + strategy() + ")";
    }
};

template<typename Strategy>
std::string call(Strategy& strategy) {
    return "call(" + strategy() + ")";
}

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {

    stateful_context<stateful_strategy_one> ctx_one;
    std::cout << ctx_one.call() << std::endl;
    std::cout << ctx_one.call() << std::endl;

    stateful_context<stateful_strategy_two> ctx_two;
    std::cout << ctx_two.call() << std::endl;
    std::cout << ctx_two.call() << std::endl;

    stateful_strategy_one str_one{};
    std::cout << call(str_one) << std::endl;
    std::cout << call(str_one) << std::endl;

    stateful_strategy_two str_two{};
    std::cout << call(str_two) << std::endl;
    std::cout << call(str_two) << std::endl;

}
