#ifndef SERVER_BLASTERBALL_H_
#define SERVER_BLASTERBALL_H_

#include "server_projectile.h"

class Blasterball : public Projectile {
    private:
        uint8_t projectile_id;

        Direction direction;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

        uint8_t damage_multiplier;

        uint8_t speed;

    public:
        Blasterball(uint8_t x, uint8_t y, uint8_t dir,
                    std::vector<uint8_t> &data) : x_pos(x), y_pos(y) {
            if (dir == LEFT) {
                direction = DIR_LEFT;
            } else if (dir == RIGHT) {
                direction = DIR_RIGHT;
            } else {
                throw std::runtime_error("Invalid projectile direction");
            }
            projectile_id = data[PR_ID_POS];
            x_hitbox = data[PR_RD_POS];
            y_hitbox = data[PR_RD_POS];
            damage = data[PR_DM_POS];
            damage_multiplier = data[PR_MP_POS];
            speed = data[PR_SP_POS];
        };
};
#endif
