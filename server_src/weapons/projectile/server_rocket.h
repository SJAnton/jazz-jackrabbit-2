#ifndef SERVER_ROCKET_H_
#define SERVER_ROCKET_H_

#include "server_projectile.h"

#define X_HITBOX 5
#define Y_HITBOX 3
#define DAMAGE 1
#define DMG_MULTIPLIER 2

class Rocket : public Projectile {
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox = X_HITBOX;

        uint8_t y_hitbox = Y_HITBOX;

        uint8_t damage = DAMAGE;

    public:
        Rocket(uint8_t x, uint8_t y) : x_pos(x), y_pos(y) {};

        void impact();
};
#endif
