#include <iostream>
#include <memory>

// -----------------------------------------------------------------------------
//   PATTERN (dynamic polymorphism)
// -----------------------------------------------------------------------------

struct data_provider {
    virtual std::string read_data() = 0;
    virtual ~data_provider() {}
};

struct data_base : data_provider {
    std::string read_data() { return "data"; }
};

struct data_compressor : data_provider {
    data_provider& wrapee;

    data_compressor(data_provider& wrapee) : wrapee(wrapee) {}

    std::string read_data() {
        return wrapee.read_data() + " -> decompress";
    }
};

struct data_encryptor : data_provider {
    data_provider& wrapee;

    data_encryptor(data_provider& wrapee) : wrapee(wrapee) {}

    std::string read_data() {
        return wrapee.read_data() + " -> decrypt";
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
    std::unique_ptr<data_compressor> compressor{new data_compressor(*db)};
    std::unique_ptr<data_encryptor> encryptor{new data_encryptor(*compressor)};
    print_data(*encryptor);
}
