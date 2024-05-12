#ifndef SERVER_RF_MISSILE_H_
#define SERVER_RF_MISSILE_H_

#include "server_weapon.h"
#include "Projectile/server_rocket.h"

#define NAME "RF Missile"
#define AMMO -1
#define FIRE_RATE 10
#define COOLDOWN 10
#define SPEED 10

class RFMissile : public Weapon {
    // Sin el power-up dispara un cohete 15° arriba y otro 15° abajo
    private:
        std::string name = NAME;

        Rocket projectile;

        uint8_t ammo = AMMO;

        uint8_t fire_rate = FIRE_RATE;

        uint8_t recharge_cooldown = COOLDOWN;

        uint8_t projectile_speed = SPEED;

    public:
        RFMissile();

        void shoot(); //override
};
#endif
