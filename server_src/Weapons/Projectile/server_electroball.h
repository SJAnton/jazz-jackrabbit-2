#ifndef SERVER_ELECTROBALL_H_
#define SERVER_ELECTROBALL_H_

#include "server_projectile.h"

class Electroball : public Projectile {
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

    public:
        Electroball(uint8_t x, uint8_t y);

        void on_hit(); //override

        void kill(); //override
};
#endif
