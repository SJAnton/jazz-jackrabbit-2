#ifndef SERVER_ICEBALL_H_
#define SERVER_ICEBALL_H_

#include "server_projectile.h"

#define RADIUS 3
#define DAMAGE 1
#define DMG_MULTIPLIER 2

class Iceball : public Projectile {
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox = RADIUS;

        uint8_t y_hitbox = RADIUS;

        uint8_t damage = DAMAGE;

    public:
        Iceball(uint8_t x, uint8_t y) : x_pos(x), y_pos(y) {};

        bool contact(Character &ch);
};
#endif
