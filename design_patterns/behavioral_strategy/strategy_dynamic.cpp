#include <iostream>
#include <memory>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

struct stateful_strategy {
    virtual ~stateful_strategy() {}
    virtual std::string operator()() = 0;
};

struct stateful_strategy_one : stateful_strategy {
    std::string state = "stateful_strategy_one";

    std::string operator()() { return state += "++"; }
};

struct stateful_strategy_two : stateful_strategy {
    std::string state = "stateful_strategy_two";

    std::string operator()() { return state += "##"; }
};

struct stateful_context {
    stateful_strategy& strategy;

    std::string call() {
        return "stateful_context::call(" + strategy() + ")";
    }
};

std::string call(stateful_strategy& strategy) {
    return "call(" + strategy() + ")";
}

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {

    std::unique_ptr<stateful_strategy> strategy_one{new stateful_strategy_one{}};
    stateful_context ctx_one{*strategy_one};
    std::cout << ctx_one.call() << std::endl;
    std::cout << ctx_one.call() << std::endl;

    std::unique_ptr<stateful_strategy> strategy_two{new stateful_strategy_two{}};
    stateful_context ctx_two{*strategy_two};
    std::cout << ctx_two.call() << std::endl;
    std::cout << ctx_two.call() << std::endl;

    std::cout << call(*strategy_one) << std::endl;
    std::cout << call(*strategy_one) << std::endl;

    std::cout << call(*strategy_one) << std::endl;
    std::cout << call(*strategy_one) << std::endl;

}
