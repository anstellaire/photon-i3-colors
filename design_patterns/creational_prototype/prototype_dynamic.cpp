#include <iostream>
#include <memory>
#include <vector>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

struct uielement {
    virtual ~uielement() = default;

    virtual std::unique_ptr<uielement> clone() const = 0;

    virtual char const* name() const {
        return "uielement";
    }
};

struct button : uielement {
    std::unique_ptr<uielement> clone() const override {
        return std::unique_ptr<uielement>(new button(*this));
    }

    char const* name() const override {
        return "button";
    }
};

struct inputbox : uielement {
    std::unique_ptr<uielement> clone() const override {
        return std::unique_ptr<uielement>(new inputbox(*this));
    }

    char const* name() const override {
        return "inputbox";
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {

    // Create a vector of uielements
    std::vector<std::unique_ptr<uielement>> uielements{};
    uielements.emplace_back(new button());
    uielements.emplace_back(new inputbox());

    // Copy using prototype patterns
    std::vector<std::unique_ptr<uielement>> uielements_copy;
    for(auto& uielement : uielements)
        uielements_copy.push_back(uielement->clone());

    // Print prototype copy
    for(auto& uielement : uielements_copy)
        std::cout << uielement->name() << std::endl;

}
