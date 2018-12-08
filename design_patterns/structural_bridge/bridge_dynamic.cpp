#include <iostream>
#include <memory>

// -----------------------------------------------------------------------------
//   PATTERN (dynamic polymorphism)
// -----------------------------------------------------------------------------

struct weapon_slot {
    virtual char const* use() = 0;
    virtual ~weapon_slot() {}
};

struct missle_weapon : weapon_slot {
    char const* use() { return "missle launch"; }
};

struct dummy_weapon : weapon_slot {
    char const* use() { return "click-click"; }
};

struct spaceship {
    std::unique_ptr<weapon_slot> slot;

    spaceship(std::unique_ptr<weapon_slot> s) : slot(std::move(s)) {}
    void set_slot(std::unique_ptr<weapon_slot> s) { slot = std::move(s); }

    virtual void attack() = 0;
    virtual ~spaceship() {}
};

struct destroyer : spaceship {
    destroyer(std::unique_ptr<weapon_slot> slot) : spaceship(std::move(slot)) {}

    void attack() {
        std::cout << "Destroyer attacks: " << slot->use() << std::endl;
    }
};

struct cruiser : spaceship {
    cruiser(std::unique_ptr<weapon_slot> slot) : spaceship(std::move(slot)) {}

    void attack() {
        std::cout << "Cruiser attacks: " << slot->use() << std::endl;
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

void unit_attack(spaceship& ship) {
    ship.attack();
}

int main() {
    std::unique_ptr<spaceship> ship{new cruiser{
        std::unique_ptr<weapon_slot>{new missle_weapon{}}
    }};

    unit_attack(*ship);

    ship->set_slot(
        std::unique_ptr<weapon_slot>{new dummy_weapon{}}
    );

    unit_attack(*ship);
}
