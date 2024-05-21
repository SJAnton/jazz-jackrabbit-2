#ifndef SERVER_ENEMY_H_
#define SERVER_ENEMY_H_

#include <vector>
#include <cstdint>

#include "server_character.h"

class Enemy : public Character {
    private:
        uint8_t health;

        uint8_t damage;

        uint8_t points;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        bool alive = true;

        bool frozen = false;

        bool contact_x(Character &ch);

        bool contact_y(Character &ch);

    public:
        Enemy() {};

        void move_x_pos(uint8_t &x);

        void move_y_pos(uint8_t &y);

        bool contact(Character &ch);
};
#endif
