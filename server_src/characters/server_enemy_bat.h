#ifndef SERVER_ENEMY_BAT_H_
#define SERVER_ENEMY_BAT_H_

#include "server_enemy.h"

class EnemyBat : public Enemy {
    private:

    public:
        EnemyBat(uint8_t x, uint8_t y, std::map<std::string, std::vector<uint8_t>> &map)
                    : Enemy(map) {
            std::vector<uint8_t> data = map[BAT_KEY];
            x_pos = x;
            y_pos = y;
            health = data[H_POS];
            enemy_id = BAT_ID;
            damage = data[D_POS];
            x_hitbox = data[XH_POS];
            y_hitbox = data[YH_POS];
            type = Bat;
            enemy_status = EstadosEnemy::Idle;
            if (health <= 0) {
                alive = false;
            }
        };
};
#endif
