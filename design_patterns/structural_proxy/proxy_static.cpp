#include <iostream>

// -----------------------------------------------------------------------------
//   PATTERN (static polymorphism + composition)
// -----------------------------------------------------------------------------

template<typename Impl>
struct data_provider {
    Impl impl;

    char const* read_data() { return impl.read_data(); }
};

struct data_base {
    char const* read_data() {
        return "data";
    }
};

template<typename Impl>
struct data_logger {
    data_provider<Impl> wrapee;

    char const* read_data() {
        std::cout << "[LOG] > reading from data base" << std::endl;
        return wrapee.read_data();
    }
};

template<typename Impl>
struct data_cacher {
    data_provider<Impl> wrapee;
    char const* cached_data;

    data_cacher(data_provider<Impl> wrapee) :
        wrapee(std::move(wrapee)), cached_data(NULL) {}

    char const* read_data() {;
        if (cached_data)
            return cached_data;

        cached_data = wrapee.read_data();
        return cached_data;
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

template<typename Impl>
void print_data(data_provider<Impl>& provider) {
    std::cout << provider.read_data() << std::endl;
}

int main() {
    data_provider<data_base> db{};
    data_provider<data_logger<data_base>> logger{db};
    data_provider<data_cacher<data_logger<data_base>>> cacher{logger};

    print_data(cacher);
    print_data(cacher);
}
