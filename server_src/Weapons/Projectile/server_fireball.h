#ifndef SERVER_FIREBALL_H_
#define SERVER_FIREBALL_H_

#include "server_projectile.h"

class Fireball : public Projectile {
    // De esta clase heredan todos los proyectiles
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

    public:
        Fireball(uint8_t x, uint8_t y);

        void on_hit(); //override

        void kill(); //overrides
};
#endif
