#ifndef SERVER_BLASTERBALL_H_
#define SERVER_BLASTERBALL_H_

#include "server_projectile.h"

class Blasterball : public Projectile {
    private:

    public:
        Blasterball(uint8_t x, uint8_t y, uint8_t dir, std::vector<uint8_t> &data) {
            if (dir == LEFT) {
                direction = DIR_LEFT;
            } else if (dir == RIGHT) {
                direction = DIR_RIGHT;
            } else {
                throw std::runtime_error("Invalid projectile direction");
            }
            x_pos = x;
            y_pos = y;
            projectile_id = data[PR_ID_POS];
            x_hitbox = data[PR_RD_POS];
            y_hitbox = data[PR_RD_POS];
            damage = data[PR_DM_POS];
            damage_multiplier = data[PR_MP_POS];
            speed = data[PR_SP_POS];
        };
};
#endif
