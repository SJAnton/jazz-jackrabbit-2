#ifndef SERVER_TOASTERBALL_H_
#define SERVER_TOASTERBALL_H_

#include "server_projectile.h"

class Toasterball : public Projectile {
    private:
        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t damage;

    public:
        Toasterball();
};
#endif
