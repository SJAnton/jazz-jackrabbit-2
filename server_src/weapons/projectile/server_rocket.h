#ifndef SERVER_ROCKET_H_
#define SERVER_ROCKET_H_

#include "server_projectile.h"

#define XH_POS 0
#define YH_POS 1
#define DM_POS 2
#define MP_POS 3

class Rocket : public Projectile {
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

        uint8_t damage_multiplier;

    public:
        Rocket(uint8_t x, uint8_t y, std::vector<uint8_t> &data) : x_pos(x), y_pos(y) {
            x_hitbox = data[XH_POS];
            y_hitbox = data[YH_POS];
            damage = data[DM_POS];
            damage_multiplier = data[MP_POS];
        };

        void impact();
};
#endif
