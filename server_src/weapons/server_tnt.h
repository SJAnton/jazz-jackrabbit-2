#ifndef SERVER_TNT_H_
#define SERVER_TNT_H_

#include "server_weapon.h"

#define NAME "TNT"
#define AMMO -1
#define FIRE_RATE 10
#define COOLDOWN 10
#define SPEED 10

class TNT : public Weapon {
    private:
        std::string name = NAME;

        uint8_t ammo = AMMO;

        uint8_t fire_rate = FIRE_RATE;

        uint8_t recharge_cooldown = COOLDOWN;

        uint8_t projectile_speed = SPEED;

    public:
        TNT();

        void shoot(); //override
};
#endif