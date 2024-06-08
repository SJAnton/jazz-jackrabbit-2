#ifndef SERVER_BOUNCER_H_
#define SERVER_BOUNCER_H_

#include "server_weapon.h"
#include "projectile/server_bouncerball.h"

#define ID_POS 0
#define AM_POS 1
#define FR_POS 2
#define RC_POS 3

class Bouncer : public Weapon {
    private:
        uint8_t weapon_id;

        uint8_t ammo;

        uint8_t fire_rate;

        uint8_t cooldown;

        std::vector<uint8_t> &data;

    public:
        Bouncer(std::vector<uint8_t> &data) : data(data) {
            weapon_id = data[ID_POS];
            ammo = data[AM_POS];
            fire_rate = data[FR_POS];
            cooldown = data[RC_POS];
        };
};
#endif
