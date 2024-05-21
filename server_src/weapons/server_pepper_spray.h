#ifndef SERVER_PEPPER_SPRAY_H_
#define SERVER_PEPPER_SPRAY_H_

#include "server_weapon.h"
#include "projectile/server_fireball.h"

#define NAME "Pepper Spray"
#define AM_POS 0
#define FR_POS 1
#define RC_POS 2
#define SP_POS 3

class PepperSpray : public Weapon {
    private:
        std::string name = NAME;

        uint8_t ammo;

        uint8_t fire_rate;

        uint8_t recharge_cooldown;

        uint8_t projectile_speed;

        std::vector<uint8_t> &data;

    public:
        PepperSpray(std::vector<uint8_t> &data) : data(data) {
            ammo = data[AM_POS];
            fire_rate = data[FR_POS];
            recharge_cooldown = data[RC_POS];
            projectile_speed = data[SP_POS];
        };

        void shoot(); //override
};
#endif