#ifndef SERVER_CHARACTER_H_
#define SERVER_CHARACTER_H_

#include <cstdint>

#include "../weapons/server_tnt.h"
#include "../weapons/server_weapon.h"
#include "../weapons/server_seeker.h"
#include "../weapons/server_blaster.h"
#include "../weapons/server_bouncer.h"
#include "../weapons/server_freezer.h"
#include "../weapons/server_toaster.h"
#include "../weapons/server_rf_missile.h"
#include "../weapons/server_pepper_spray.h"
#include "../weapons/server_electro_blaster.h"

class Character {
    private:
        uint8_t health;

        Weapon weapon;

        uint8_t points;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        bool alive = true;

        bool frozen = false;

        bool intoxicated = false;
    public:
        Character() {};
};
#endif
