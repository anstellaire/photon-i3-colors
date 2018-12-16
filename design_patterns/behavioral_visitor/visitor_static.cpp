#include <iostream>

struct spaceship;
struct spaceship_engine;
struct spaceship_control_systems;
struct spaceship_flight_system;
struct spaceship_combat_system;

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

template<typename Impl>
struct module {
    Impl impl;

    void visit(spaceship_engine& engine) { impl.visit(engine); }
    void visit(spaceship_flight_system& fsystems) { impl.visit(fsystems); }
    void visit(spaceship_combat_system& csystems) { impl.visit(csystems); }
};

struct check_module {
    void visit(spaceship_engine&) {
        std::cout << "[CHECK] > spaceship engine.............[OK]" << std::endl;
    }

    void visit(spaceship_flight_system&) {
        std::cout << "[CHECK] > spaceship flight systems.....[OK]" << std::endl;
    }

    void visit(spaceship_combat_system&) {
        std::cout << "[CHECK] > spaceship combat systems.....[OK]" << std::endl;
    }
};

struct repair_module {
    void visit(spaceship_engine&) {
        std::cout << "[REPAIR] > spaceship engine............[OK]" << std::endl;
    }

    void visit(spaceship_flight_system&) {
        std::cout << "[REPAIR] > spaceship flight systems....[OK]" << std::endl;
    }

    void visit(spaceship_combat_system&) {
        std::cout << "[REPAIR] > spaceship combat systems....[OK]" << std::endl;
    }
};

// struct multi_module {
//     void visit(spaceship_engine& engine) {
//         if (module<check_module>{}.visit(engine) == 0)
//             module<repair_module>{}.visit(engine);
//     }
// };

struct spaceship_engine {
    template<typename Impl>
    void accept(module<Impl> mod) { mod.visit(*this); }
};

struct spaceship_combat_system {
    template<typename Impl>
    void accept(module<Impl> mod) { mod.visit(*this); }
};

struct spaceship_flight_system {
    template<typename Impl>
    void accept(module<Impl> mod) { mod.visit(*this); }
};

struct spaceship_control_systems {
    spaceship_flight_system fsystem;
    spaceship_combat_system csystem;

    template<typename Impl>
    void accept(module<Impl> mod) {
        fsystem.accept(mod);
        csystem.accept(mod);
    }
};

struct spaceship {
    spaceship_engine engine;
    spaceship_control_systems control;

    template<typename Impl>
    void accept(module<Impl> mod) {
        engine.accept(mod);
        control.accept(mod);
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    spaceship ship;

    module<check_module> ch_mod;
    ship.accept(ch_mod);

    module<repair_module> rp_mod;
    ship.accept(rp_mod);
}
