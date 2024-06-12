#ifndef SERVER_ROCKET_H_
#define SERVER_ROCKET_H_

#include "server_projectile.h"

class Rocket : public Projectile {
    private:

    public:
        Rocket(uint8_t x, uint8_t y, uint8_t dir, std::vector<uint8_t> &data) {
            if (dir == LEFT) {
                direction = Left;
            } else if (dir == RIGHT) {
                direction = Right;
            } else {
                throw std::runtime_error("Invalid projectile direction");
            }
            x_pos = x;
            y_pos = y;
            projectile_id = data[RK_ID_POS];
            x_hitbox = data[RK_XH_POS];
            y_hitbox = data[RK_YH_POS];
            damage = data[RK_DM_POS];
            damage_multiplier = data[RK_MP_POS];
            speed = data[RK_SP_POS];
        };

        void impact();
};
#endif
