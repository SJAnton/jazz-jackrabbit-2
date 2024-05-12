#ifndef SERVER_WEAPON_H_
#define SERVER_WEAPON_H_

#include <string>

class Weapon {
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
