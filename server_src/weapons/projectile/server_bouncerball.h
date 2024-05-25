#ifndef SERVER_BOUNCERBALL_H_
#define SERVER_BOUNCERBALL_H_

#include "server_projectile.h"

#define PR_ID_POS 0
#define PR_RD_POS 1
#define PR_DM_POS 2
#define PR_MP_POS 3

class Bouncerball : public Projectile {
    private:
        uint8_t projectile_id;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

        uint8_t damage_multiplier;

    public:
        Bouncerball(uint8_t x, uint8_t y, std::vector<uint8_t> &data) : x_pos(x), y_pos(y) {
            projectile_id = data[PR_ID_POS];
            x_hitbox = data[PR_RD_POS];
            y_hitbox = data[PR_RD_POS];
            damage = data[PR_DM_POS];
            damage_multiplier = data[PR_MP_POS];
        };
};
#endif
