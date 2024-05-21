#ifndef SERVER_BLASTERBALL_H_
#define SERVER_BLASTERBALL_H_

#include "server_projectile.h"

#define RD_POS 0
#define DM_POS 1
#define MP_POS 2

class Blasterball : public Projectile {
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

        uint8_t damage_multiplier;

    public:
        Blasterball(uint8_t x, uint8_t y, std::vector<uint8_t> &data) : x_pos(x), y_pos(y) {
            x_hitbox = data[RD_POS];
            y_hitbox = data[RD_POS];
            damage = data[DM_POS];
            damage_multiplier = data[MP_POS];
        };
};
#endif
