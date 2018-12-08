#include <iostream>
#include <memory>

// -----------------------------------------------------------------------------
//   PATTERN: ADAPTER (dynamic polymorphism)
// -----------------------------------------------------------------------------

struct weapon_slot {
    virtual ~weapon_slot() {}
    virtual char const* use() = 0;
};

struct missle_weapon : weapon_slot {
    char const* use() { return "missle launch"; }
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

struct fuel_tank_adapter : weapon_slot {
    fuel_tank tank;

    fuel_tank_adapter(fuel_tank tank) : tank(tank) {}

    char const* use() {
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

struct spaceship {
    std::unique_ptr<weapon_slot> slot;

    void attack() { std::cout << slot->use() << std::endl; }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

void unit_attack(spaceship& ship) {
    ship.attack();
}

int main() {
    spaceship spaceship_with_missles{std::unique_ptr<missle_weapon>{
        new missle_weapon{}
    }};

    unit_attack(spaceship_with_missles);

    fuel_tank tank{1.0, 0.2};
    spaceship spaceship_with_adapter{std::unique_ptr<fuel_tank_adapter>{
        new fuel_tank_adapter{tank}
    }};

    unit_attack(spaceship_with_adapter);
    unit_attack(spaceship_with_adapter);
}
