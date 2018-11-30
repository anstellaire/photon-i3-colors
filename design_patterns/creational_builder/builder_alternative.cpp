#include "utils.hpp"

#include <iostream>
#include <array>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

class starship_config {
    starship_engine engine_;
    starship_weapon weapon_;
public:
    starship_config& set_engine(starship_engine engine) {
        engine_ = engine;
        return *this;
    }

    starship_config& set_weapon(starship_weapon weapon) {
        weapon_ = weapon;
        return *this;
    }

    starship_engine& get_engine() {
        return engine_;
    }

    starship_weapon& get_weapon() {
        return weapon_;
    }

    static starship_config get_alpha_starship_config() {
        return starship_config{}
            .set_engine(starship_ion_engine{})
            .set_weapon(starship_laser_weapon{});
    }
};

struct starship {
    starship_engine engine;
    starship_weapon weapon;

    starship(starship_config config) :
        engine(config.get_engine()), weapon(config.get_weapon()) {}
};

struct destroyer : starship {
    destroyer(starship_config config) : starship(config) {}
};

struct cruiser : starship {
    cruiser(starship_config config) : starship(config) {}
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    starship_config delta_starship_config = starship_config{}
        .set_engine(starship_plasma_engine{})
        .set_weapon(starship_cannon_weapon{});

    std::array<starship, 4> squad = {
        starship{starship_config::get_alpha_starship_config()},
        starship{starship_config::get_alpha_starship_config()},
        starship{delta_starship_config},
        starship{delta_starship_config},
    };

    for (std::size_t i = 0; i < squad.size(); ++i) {
        std::cout << "Ship #" << i << std::endl;
        std::cout << " - Weapon: " << squad[i].weapon.descritpion << std::endl;
        std::cout << " - Engine: " << squad[i].engine.descritpion << std::endl;
    }
}
