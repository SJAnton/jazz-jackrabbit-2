#ifndef SERVER_ROCKET_H_
#define SERVER_ROCKET_H_

#include "server_projectile.h"

#define RK_ID_POS 0
#define RK_XH_POS 1
#define RK_YH_POS 2
#define RK_DM_POS 3
#define RK_MP_POS 4

class Rocket : public Projectile {
    private:
        uint8_t projectile_id;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

        uint8_t damage_multiplier;

    public:
        Rocket(uint8_t x, uint8_t y, std::vector<uint8_t> &data) : x_pos(x), y_pos(y) {
            projectile_id = data[RK_ID_POS];
            x_hitbox = data[RK_XH_POS];
            y_hitbox = data[RK_YH_POS];
            damage = data[RK_DM_POS];
            damage_multiplier = data[RK_MP_POS];
        };

        void impact();
};
#endif
