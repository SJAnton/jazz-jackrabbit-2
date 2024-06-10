#ifndef SERVER_ENEMY_H_
#define SERVER_ENEMY_H_

#include <vector>
#include <cstdint>

#include "server_character.h"

class Enemy : public Character {
    private:
        bool contact_x(Character &ch);

        bool contact_y(Character &ch);

    protected:
        uint8_t damage;
        
    public:
        Enemy() {};

        void move_x_pos(uint8_t &x);

        void move_y_pos(uint8_t &y);

        bool contact(Character &ch);
};
#endif
