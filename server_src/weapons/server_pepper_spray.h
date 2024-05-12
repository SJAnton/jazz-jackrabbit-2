#ifndef SERVER_PEPPER_SPRAY_H_
#define SERVER_PEPPER_SPRAY_H_

#include "server_weapon.h"
#include "projectile/server_fireball.h"

#define NAME "Pepper Spray"
#define AMMO -1
#define FIRE_RATE 10
#define COOLDOWN 10
#define SPEED 10

class PepperSpray : public Weapon {
    private:
        std::string name = NAME;

        Fireball projectile;

        uint8_t ammo = AMMO;

        uint8_t fire_rate = FIRE_RATE;

        uint8_t recharge_cooldown = COOLDOWN;

        uint8_t projectile_speed = SPEED;

    public:
        PepperSpray();

        void shoot(); //override
};
#endif