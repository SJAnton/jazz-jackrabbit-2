#ifndef SERVER_SEEKER_ROCKET_H_
#define SERVER_SEEKER_ROCKET_H_

#include "server_projectile.h"

class SeekerRocket : public Projectile {
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

    public:
        SeekerRocket(uint8_t x, uint8_t y);
        
        void on_hit(); //override

        void kill(); //override
};
#endif
