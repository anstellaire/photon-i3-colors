#include <iostream>
#include <memory>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

struct command {
    virtual ~command() {}
    virtual void run() = 0;
};

struct save_command : command {
    void run() {
        std::cout << " > Save(app::get_active_file)" << std::endl;
    }
};

struct open_command : command  {
    void run() {
        std::cout << " > Open(app::get_file_name_dialog)" << std::endl;
    }
};

struct element {
    command& cmd;
    element(command& cmd) : cmd(cmd) {}

    void use() { cmd.run(); }
};

struct button : element {
    button(command& cmd) : element(cmd) {}
    /* button attributes */
};

struct shortcut : element {
    shortcut(command& cmd) : element(cmd) {}
    /* shortcut attributes */
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    save_command save_cmd{};
    open_command open_cmd{};

    button save_button{save_cmd};
    shortcut save_shortcut{save_cmd};

    button open_button{open_cmd};
    shortcut open_shortcut{open_cmd};

    save_button.use();
    save_shortcut.use();
    open_button.use();
    open_shortcut.use();
}
