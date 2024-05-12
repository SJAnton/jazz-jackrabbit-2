#ifndef SERVER_FREEZER_H_
#define SERVER_FREEZER_H_

#include "server_weapon.h"
#include "projectile/server_iceball.h"

#define NAME "Freezer"
#define AMMO -1
#define FIRE_RATE 10
#define COOLDOWN 10
#define SPEED 10

class Freezer : public Weapon {
    private:
        std::string name = NAME;

        Iceball projectile;

        uint8_t ammo = AMMO;

        uint8_t fire_rate = FIRE_RATE;

        uint8_t recharge_cooldown = COOLDOWN;

        uint8_t projectile_speed = SPEED;

    public:
        Freezer();

        void shoot(); //override
};
#endif
