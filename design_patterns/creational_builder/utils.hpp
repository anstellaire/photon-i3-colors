#pragma once

// -----------------------------------------------------------------------------
//   STARSHIP ENGINE
// -----------------------------------------------------------------------------

struct starship_engine {
    char const* descritpion;
};

struct starship_ion_engine : starship_engine {
    starship_ion_engine() : starship_engine{
        "Ion Engine. What a wonderful xenon light!"} {}
};

struct starship_plasma_engine : starship_engine {
    starship_plasma_engine() : starship_engine{
        "Plasma Engine. Do you have a pocket nuclear reactor for this?"} {}
};

// -----------------------------------------------------------------------------
//   STARSHIP WEAPON
// -----------------------------------------------------------------------------

struct starship_weapon {
    char const* descritpion;
};

struct starship_laser_weapon : starship_weapon {
    starship_laser_weapon() : starship_weapon{
        "The blue glow seems to have a lulling effect"} {}
};

struct starship_cannon_weapon : starship_weapon {
    starship_cannon_weapon() : starship_weapon{
        "What? In space? Happy flight!"} {}
};
