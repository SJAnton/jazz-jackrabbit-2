#ifndef SERVER_WEAPON_H_
#define SERVER_WEAPON_H_

#include <vector>
#include <cstdint>

#define ID_POS 0
#define AM_POS 1
#define FR_POS 2
#define RC_POS 3

class Weapon {
    // https://www.jazz2online.com/21/the-weapons-of-jazz2/
    protected:
        uint8_t weapon_id;

        uint8_t ammo;

        uint8_t fire_rate;

        uint8_t cooldown;

    public:
        Weapon() {};

        virtual ~Weapon() = default;

        virtual bool shoot();

        uint8_t get_id();

        uint8_t get_ammo();
};
#endif
