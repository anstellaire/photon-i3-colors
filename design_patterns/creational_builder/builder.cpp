#include "utils.hpp"

#include <iostream>
#include <array>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

struct starship {
    starship_engine engine;
    starship_weapon weapon;
};

class starship_builder {
    starship_engine engine_;
    starship_weapon weapon_;
public:
    starship_builder& set_engine(starship_engine engine) {
        engine_ = engine;
        return *this;
    }

    starship_builder& set_weapon(starship_weapon weapon) {
        weapon_ = weapon;
        return *this;
    }

    starship build() {
        return starship{engine_, weapon_};
    }

    static starship build_alpha_starship() {
        return starship{starship_ion_engine{}, starship_laser_weapon{}};
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    starship_builder delta_starship_builder = starship_builder{}
        .set_engine(starship_plasma_engine{})
        .set_weapon(starship_cannon_weapon{});

    std::array<starship, 4> squad = {
        starship_builder::build_alpha_starship(),
        starship_builder::build_alpha_starship(),
        delta_starship_builder.build(),
        delta_starship_builder.build(),
    };

    for (std::size_t i = 0; i < squad.size(); ++i) {
        std::cout << "Ship #" << i << std::endl;
        std::cout << " - Weapon: " << squad[i].weapon.descritpion << std::endl;
        std::cout << " - Engine: " << squad[i].engine.descritpion << std::endl;
    }
}
