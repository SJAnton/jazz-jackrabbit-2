#ifndef SERVER_WEAPON_H_
#define SERVER_WEAPON_H_

#include <string>

#include "Projectile/server_projectile.h"

class Weapon {
    // https://www.jazz2online.com/21/the-weapons-of-jazz2/
    // De esta clase heredan todas las armas
    // Añadir propiedades especiales para cada arma
    private:
        std::string name;

        uint8_t ammo;

        uint8_t fire_rate;

        uint8_t recharge_cooldown;

        uint8_t projectile_speed;

    public:
        Weapon();

        void shoot();
};
#endif
