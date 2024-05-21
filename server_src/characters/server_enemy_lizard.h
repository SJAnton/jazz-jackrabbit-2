#ifndef SERVER_ENEMY_LIZARD_H_
#define SERVER_ENEMY_LIZARD_H_

#include "server_enemy.h"

#define H_POS 0
#define D_POS 1
#define XH_POS 2
#define YH_POS 3

class EnemyLizard : public Enemy {
    private:
        uint8_t health;

        uint8_t damage;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        bool alive = true;

        bool frozen = false;

    public:
        EnemyLizard(uint8_t x, uint8_t y, std::vector<uint8_t> &data) : x_pos(x), y_pos(y) {
            health = data[H_POS];
            damage = data[D_POS];
            x_hitbox = data[XH_POS];
            y_hitbox = data[YH_POS];
            if (health <= 0) {
                alive = false;
            }
        };
};
#endif