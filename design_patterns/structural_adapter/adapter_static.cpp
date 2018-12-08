#include <iostream>

// -----------------------------------------------------------------------------
//   PATTERN: ADAPTER (static polymorphism + composition)
// -----------------------------------------------------------------------------

template<typename Impl>
struct weapon_slot {
    Impl impl;

    char const* use() { return impl.use_impl(); }
};

struct missle_weapon {
    char const* use_impl() { return "missle launch"; }
};

struct fuel_tank {
    float max_volume;
    float cur_volume;

    float refuel(float volume) {
        float available_volume = volume > cur_volume ? cur_volume : volume;
        cur_volume -= available_volume;
        return available_volume;
    }
};

struct fuel_tank_adapter {
    fuel_tank tank;

    char const* use_impl() {
        float available_volume = tank.refuel(tank.max_volume*0.25);

        if (available_volume > 0.f)
            return "refueling activated";
        else
            return "refueling failed (the fuel tank is empty)";
    }
};

// -----------------------------------------------------------------------------
//   PATTERN: USER
// -----------------------------------------------------------------------------

template<typename Weapon>
struct spaceship {
    weapon_slot<Weapon> slot;

    void attack() { std::cout << slot.use() << std::endl; }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

template<typename Weapon>
void unit_attack(spaceship<Weapon>& ship) {
    ship.attack();
}

int main() {
    spaceship<missle_weapon> spaceship_with_missles{missle_weapon{}};

    unit_attack(spaceship_with_missles);

    fuel_tank tank{1.0, 0.2};
    spaceship<fuel_tank_adapter> spaceship_with_adapter{fuel_tank_adapter{tank}};

    unit_attack(spaceship_with_adapter);
    unit_attack(spaceship_with_adapter);
}
