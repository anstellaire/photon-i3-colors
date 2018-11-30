#include <iostream>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

// use:
// - to provide a single access point to a shared resource
// - to group global variables

class singleton {

    singleton() = default;
    singleton(singleton const&) = delete;
    singleton(singleton&&) = delete;
    singleton& operator=(singleton const&) = delete;
    singleton& operator=(singleton&&) = delete;

    int answer = 42;

public:

    static singleton& instance() {
        static singleton instance;
        return instance;
    }

    void print_name() {
        std::cout << "The answer is " << answer++ << std::endl;
    }

};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    singleton::instance().print_name();
    singleton::instance().print_name();
}
