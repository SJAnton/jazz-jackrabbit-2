#ifndef SERVER_PROJECTILE_H_
#define SERVER_PROJECTILE_H_

#include <cstdint>

#include "../../characters/server_character.h"

class Projectile {
    // De esta clase heredan todos los proyectiles
    // https://www.jazz2online.com/21/the-weapons-of-jazz2/
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

        bool powered_up = false;
        
    protected:
        bool contact_x(Character &ch);

        bool contact_y(Character &ch);

    public:
        Projectile();

        uint8_t left_side();

        uint8_t right_side();

        uint8_t upper_side();

        uint8_t lower_side();

        bool is_powered_up();

        void move(uint8_t x, uint8_t y);

        void move_x_pos(uint8_t &x);

        void move_y_pos(uint8_t &y);

        void power_up();

        void power_up_end();

        bool contact(Character &ch);
};
#endif
