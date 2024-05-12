#ifndef SERVER_BOUNCERBALL_H_
#define SERVER_BOUNCERBALL_H_

#include "server_projectile.h"

#define RADIUS 3
#define DAMAGE 1
#define DMG_MULTIPLIER 2

class Bouncerball : public Projectile {
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox = RADIUS;

        uint8_t y_hitbox = RADIUS;

        uint8_t damage = DAMAGE;

    public:
        Bouncerball(uint8_t x, uint8_t y) : x_pos(x), y_pos(y) {};

        void move_x_pos(uint8_t &x); // x_pos + x

        void move_y_pos(uint8_t &y); // y_pos + y

        void powerup();

        void powerup_end();

        bool contact();
};
#endif
