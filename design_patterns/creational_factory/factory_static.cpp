#include <iostream>

// -----------------------------------------------------------------------------
//   PATTERN: PRODUCT TYPE
// -----------------------------------------------------------------------------

struct linux_button {
    char const* name() const {
        return "Linux button";
    }
};

struct linux_checkbox {
    char const* name() const {
        return "Linux checkbox";
    }
};

struct windows_button {
    char const* name() const {
        return "Windows button";
    }
};

struct windows_checkbox {
    char const* name() const {
        return "Windows checkbox";
    }
};

// -----------------------------------------------------------------------------
//   PATTERN: FACTORY TYPE
// -----------------------------------------------------------------------------

template<typename Impl>
struct gui {
    Impl impl;

    auto create_button() const -> decltype(impl.create_button()) {
        return impl.create_button();
    }

    auto create_checkbox() const -> decltype(impl.create_checkbox()) {
        return impl.create_checkbox();
    }
};

struct linux_gui {
    linux_button create_button() const {
        return linux_button{};
    }

    linux_checkbox create_checkbox() const {
        return linux_checkbox{};
    }
};

struct windows_gui {
    windows_button create_button() const {
        return windows_button{};
    }

    windows_checkbox create_checkbox() const {
        return windows_checkbox{};
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

template<typename Impl>
void enumerate_gui_elements(gui<Impl> gui) {
    std::cout << gui.create_button().name() << std::endl;
    std::cout << gui.create_checkbox().name() << std::endl;
}

int main() {
    enumerate_gui_elements(gui<linux_gui>{});
    enumerate_gui_elements(gui<windows_gui>{});
}
