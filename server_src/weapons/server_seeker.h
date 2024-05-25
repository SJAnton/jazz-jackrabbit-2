#ifndef SERVER_SEEKER_H_
#define SERVER_SEEKER_H_

#include "server_weapon.h"
#include "projectile/server_seeker_rocket.h"

#define ID_POS 0
#define AM_POS 1
#define FR_POS 2
#define RC_POS 3
#define SP_POS 4

class Seeker : public Weapon {
    private:
        uint8_t weapon_id;

        uint8_t ammo;

        uint8_t fire_rate;

        uint8_t recharge_cooldown;

        uint8_t projectile_speed;

        std::vector<uint8_t> &data;

    public:
        Seeker(std::vector<uint8_t> &data) : data(data) {
            weapon_id = data[ID_POS];
            ammo = data[AM_POS];
            fire_rate = data[FR_POS];
            recharge_cooldown = data[RC_POS];
            projectile_speed = data[SP_POS];
        };

        void shoot(); //override
};
#endif
