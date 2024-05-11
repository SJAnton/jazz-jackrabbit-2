#ifndef SERVER_WEAPON_H_
#define SERVER_WEAPON_H_

#include <string>

class Weapon {
    // De esta clase heredan todas las armas
    private:
        std::string name;

        uint8_t ammo;

        uint8_t fire_rate;

    public:
        Weapon();
};
#endif
