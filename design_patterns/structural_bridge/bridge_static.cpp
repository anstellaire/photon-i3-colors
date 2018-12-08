#include <iostream>

// -----------------------------------------------------------------------------
//   PATTERN (static polymorphism + composition)
// -----------------------------------------------------------------------------

template<typename Type>
struct weapon_slot {
    Type type;

    char const* use() { return type.use_impl(); }
};

struct missle_weapon {
    char const* use_impl() { return "missle launch"; }
};

struct dummy_weapon {
    char const* use_impl() { return "click-click"; }
};

template<typename Type, typename Weapon>
struct spaceship {
    Type type;
    weapon_slot<Weapon> slot;

    void attack() { return type.attack_impl(slot.use()); }
};

struct destroyer {
    void attack_impl(char const* wpn_sound) {
        std::cout << "Destroyer attacks: " << wpn_sound << std::endl;
    }
};

struct cruiser {
    void attack_impl(char const* wpn_sound) {
        std::cout << "Cruiser attacks: " << wpn_sound << std::endl;
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

template<typename Type, typename Weapon>
void unit_attack(spaceship<Type, Weapon> ship) {
    ship.attack();
}

int main() {
    unit_attack(spaceship<cruiser, missle_weapon>{});
    unit_attack(spaceship<cruiser, dummy_weapon>{});
    unit_attack(spaceship<destroyer, missle_weapon>{});
    unit_attack(spaceship<destroyer, dummy_weapon>{});
}
