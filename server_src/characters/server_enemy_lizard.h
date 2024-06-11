#ifndef SERVER_ENEMY_LIZARD_H_
#define SERVER_ENEMY_LIZARD_H_

#include "server_enemy.h"

#define H_POS 0
#define D_POS 1
#define XH_POS 2
#define YH_POS 3

class EnemyLizard : public Enemy {
    private:

    public:
        EnemyLizard(uint8_t x, uint8_t y, std::map<std::string, std::vector<uint8_t>> &map)
                    : Enemy(map) {
            std::vector<uint8_t> data = map[LIZARD_KEY];
            x_pos = x;
            y_pos = y;
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