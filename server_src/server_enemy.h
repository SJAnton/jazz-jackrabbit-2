#ifndef SERVER_ENEMY_H_
#define SERVER_ENEMY_H_

#include <cstdint>

class Enemy {
    // De esta clase heredan todos los enemigos,
    // hay que implementar al menos tres
    private:
        uint8_t health;

        uint8_t damage;

        uint8_t points;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

    public:
        Enemy();
};
#endif
