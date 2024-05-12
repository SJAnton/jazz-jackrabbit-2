#ifndef SERVER_PROJECTILE_H_
#define SERVER_PROJECTILE_H_

#include <cstdint>

class Projectile {
    // De esta clase heredan todos los proyectiles
    // https://www.jazz2online.com/21/the-weapons-of-jazz2/
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

    public:
        Projectile();

        void move_x_pos(uint8_t x); // x_pos + x

        void move_y_pos(uint8_t y); // y_pos + y
        
        void powerup();

        void powerup_end();

        void contact();
};
#endif
