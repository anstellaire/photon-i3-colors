#include <iostream>

// -----------------------------------------------------------------------------
//   PATTERN (static polymorphism + composition)
// -----------------------------------------------------------------------------

template<typename Impl>
struct data_provider {
    Impl impl;

    std::string read_data() { return impl.read_data(); }
};

struct data_base {
    std::string read_data() { return "data"; }
};

template<typename Impl>
struct data_compressor {
    data_provider<Impl>& wrapee;

    std::string read_data() {
        return wrapee.read_data() + " -> decompress";
    }
};

template<typename Impl>
struct data_encryptor {
    data_provider<Impl>& wrapee;

    std::string read_data() {
        return wrapee.read_data() + " -> decrypt";
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

template<typename Impl>
void print_data(data_provider<Impl> provider) {
    std::cout << provider.read_data() << std::endl;
}

int main() {
    data_provider<data_base> db{};
    data_provider<data_compressor<data_base>> compressor{db};
    data_provider<data_encryptor<data_compressor<data_base>>> encryptor{compressor};

    print_data(encryptor);
}
