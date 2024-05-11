#ifndef SERVER_PROJECTILE_H_
#define SERVER_PROJECTILE_H_

#include <cstdint>

class Projectile {
    // De esta clase heredan todos los proyectiles
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

    public:
        Projectile();
};
#endif
