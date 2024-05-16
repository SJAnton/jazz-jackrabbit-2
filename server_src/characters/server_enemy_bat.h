#ifndef SERVER_ENEMY_BAT_H_
#define SERVER_ENEMY_BAT_H_

#include "server_enemy.h"

#define HEALTH 100
#define DAMAGE 1
#define X_HITBOX 5
#define Y_HITBOX 3

class EnemyBat : public Enemy {
    private:
        uint8_t health = HEALTH;

        uint8_t damage = DAMAGE;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox = X_HITBOX;

        uint8_t y_hitbox = Y_HITBOX;

        bool alive = true;

        bool frozen = false;

    public:
        EnemyBat(uint8_t x, uint8_t y) : x_pos(x), y_pos(y) {};
};
#endif
