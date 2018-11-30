#include <iostream>
#include <memory>

// -----------------------------------------------------------------------------
//   PATTERN: PRODUCT TYPE
// -----------------------------------------------------------------------------

struct button {
    virtual ~button() = default;
    virtual char const* name() const = 0;
};

struct checkbox {
    virtual ~checkbox() = default;
    virtual char const* name() const = 0;
};

struct linux_button : button {
    virtual char const* name() const override {
        return "Linux button";
    }
};

struct linux_checkbox : checkbox {
    virtual char const* name() const override {
        return "Linux checkbox";
    }
};

struct windows_button : button {
    virtual char const* name() const override {
        return "Windows button";
    }
};

struct windows_checkbox : checkbox {
    virtual char const* name() const override {
        return "Windows checkbox";
    }
};

// -----------------------------------------------------------------------------
//   PATTERN: FACTORY TYPE
// -----------------------------------------------------------------------------

struct gui {
    virtual ~gui() = default;
    virtual std::unique_ptr<button> create_button() const = 0;
    virtual std::unique_ptr<checkbox> create_checkbox() const = 0;
};

struct linux_gui : gui {
    virtual std::unique_ptr<button> create_button() const {
        return std::unique_ptr<button>(new linux_button());
    }

    virtual std::unique_ptr<checkbox> create_checkbox() const {
        return std::unique_ptr<checkbox>(new linux_checkbox());
    }
};

struct windows_gui : gui {
    virtual std::unique_ptr<button> create_button() const {
        return std::unique_ptr<button>(new windows_button());
    }

    virtual std::unique_ptr<checkbox> create_checkbox() const {
        return std::unique_ptr<checkbox>(new windows_checkbox());
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

void enumerate_gui(gui& gui) {
    std::cout << gui.create_button()->name() << std::endl;
    std::cout << gui.create_checkbox()->name() << std::endl;
}

int main() {
    enumerate_gui(*std::unique_ptr<gui>{new linux_gui});
    enumerate_gui(*std::unique_ptr<gui>{new windows_gui});
}
