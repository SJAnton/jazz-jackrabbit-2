#ifndef SERVER_WEAPON_H_
#define SERVER_WEAPON_H_

#include <vector>
#include <cstdint>

class Weapon {
    // https://www.jazz2online.com/21/the-weapons-of-jazz2/
    // De esta clase heredan todas las armas
    // Añadir propiedades especiales para cada arma
    private:
        uint8_t weapon_id;

        uint8_t ammo;

        uint8_t fire_rate;

        uint8_t recharge_cooldown;

        uint8_t projectile_speed;

    public:
        Weapon() {};

        void shoot();

        uint8_t get_id();
};
#endif
