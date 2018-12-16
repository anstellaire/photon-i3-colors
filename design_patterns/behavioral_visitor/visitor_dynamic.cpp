#include <iostream>
#include <memory>

class spaceship;
class spaceship_engine;
class spaceship_control_systems;
class spaceship_flight_system;
class spaceship_combat_system;

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

struct module {
    virtual ~module() {}
    virtual void visit(spaceship_engine& engine) = 0;
    virtual void visit(spaceship_flight_system& fsystems) = 0;
    virtual void visit(spaceship_combat_system& csystems) = 0;
};

struct check_module : module {
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

struct repair_module : module {
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

// struct multi_module : module {
//     void visit(spaceship_engine& engine) {
//         if (module<check_module>{}.visit(engine) == 0)
//             module<repair_module>{}.visit(engine);
//     }
// };

class spaceship_engine {
public:
    void accept(module& mod) { mod.visit(*this); }
};

class spaceship_combat_system {
public:
    void accept(module& mod) { mod.visit(*this); }
};

class spaceship_flight_system {
public:
    void accept(module& mod) { mod.visit(*this); }
};

class spaceship_control_systems {
    spaceship_flight_system fsystem;
    spaceship_combat_system csystem;
public:
    void accept(module& mod) {
        fsystem.accept(mod);
        csystem.accept(mod);
    }
};

class spaceship {
    spaceship_engine engine;
    spaceship_control_systems control;
public:
    void accept(module& mod) {
        engine.accept(mod);
        control.accept(mod);
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    spaceship ship;

    std::unique_ptr<module> ch_mod{new check_module{}};
    ship.accept(*ch_mod);

    std::unique_ptr<module> rp_mod{new repair_module{}};
    ship.accept(*rp_mod);
}
