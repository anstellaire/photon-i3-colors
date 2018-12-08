#include <iostream>
#include <memory>

// -----------------------------------------------------------------------------
//   PATTERN (dynamic polymorphism)
// -----------------------------------------------------------------------------

struct data_provider {
    virtual char const* read_data() = 0;
    virtual ~data_provider() {}
};

struct data_base : data_provider {
    char const* read_data() {
        return "data";
    }
};

struct data_logger : data_provider {
    std::unique_ptr<data_provider> wrapee;

    data_logger(std::unique_ptr<data_provider> wrapee) :
        wrapee(std::move(wrapee)) {}

    char const* read_data() {
        std::cout << "[LOG] > reading from data base" << std::endl;
        return wrapee->read_data();
    }
};

struct data_cacher : data_provider {
    std::unique_ptr<data_provider> wrapee;
    char const* cached_data;

    data_cacher(std::unique_ptr<data_provider> wrapee) :
        wrapee(std::move(wrapee)), cached_data(nullptr) {}

    char const* read_data() {
        if (cached_data)
            return cached_data;

        cached_data = wrapee->read_data();
        return cached_data;
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

void print_data(data_provider& provider) {
    std::cout << provider.read_data() << std::endl;
}

int main() {
    std::unique_ptr<data_base> db{new data_base{}};
    std::unique_ptr<data_logger> logger{new data_logger(std::move(db))};
    std::unique_ptr<data_cacher> cacher{new data_cacher(std::move(logger))};

    print_data(*cacher);
    print_data(*cacher);
}
