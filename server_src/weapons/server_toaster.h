#ifndef SERVER_TOASTER_H_
#define SERVER_TOASTER_H_

#include "server_weapon.h"
#include "projectile/server_toasterball.h"

#define NAME "Toaster"
#define AMMO -1
#define FIRE_RATE 10
#define COOLDOWN 10
#define SPEED 10

class Toaster : public Weapon {
    private:
        std::string name = NAME;

        Toasterball projectile;

        uint8_t ammo = AMMO;

        uint8_t fire_rate = FIRE_RATE;

        uint8_t recharge_cooldown = COOLDOWN;

        uint8_t projectile_speed = SPEED;

    public:
        Toaster();

        void shoot(); //override
};
#endif