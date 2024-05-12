#ifndef SERVER_ICEBALL_H_
#define SERVER_ICEBALL_H_

#include "server_projectile.h"

class Iceball : public Projectile {
    // De esta clase heredan todos los proyectiles
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

    public:
        Iceball();
};
#endif
