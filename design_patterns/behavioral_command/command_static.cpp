#include <iostream>
#include <memory>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

template<typename Type>
struct command {
    Type type;
    void run() { type.run(); }
};

struct save_command {
    void run() {
        std::cout << " > Save(app::get_active_file)" << std::endl;
    }
};

struct open_command {
    void run() {
        std::cout << " > Open(app::get_file_name_dialog)" << std::endl;
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

template<typename Type, typename CommandType>
struct element {
    Type type;
    command<CommandType> cmd;

    void use() { cmd.run(); }
};

struct button {
    /* button attributes */
};

struct shortcut {
    /* shortcut attributes */
};

int main() {
    element<button, save_command> save_button{};
    element<shortcut, save_command> save_shortcut{};
    element<button, open_command> open_button{};
    element<shortcut, open_command> open_shortcut{};

    save_button.use();
    save_shortcut.use();
    open_button.use();
    open_shortcut.use();
}
