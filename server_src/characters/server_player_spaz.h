#ifndef SERVER_PLAYER_SPAZ_H_
#define SERVER_PLAYER_SPAZ_H_

#include "server_character.h"

#define X_START 0
#define Y_START 0

#define HP_POS 0
#define PT_POS 1
#define XH_POS 2
#define YH_POS 3
#define JH_POS 4

class PlayerSpaz : public Character {
    private:
        uint8_t health;

        Weapon weapon;

        uint8_t points;

        uint8_t x_pos = X_START;

        uint8_t y_pos = Y_START;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        uint8_t jump_height;

        bool alive = true;

        bool frozen = false;

        bool intoxicated = false;
        
    public:
        PlayerSpaz(std::vector<uint8_t> &data) : weapon(Blaster(data)) {
            health = data[HP_POS];
            points = data[PT_POS];
            x_hitbox = data[XH_POS];
            y_hitbox = data[YH_POS];
            jump_height = data[JH_POS];
            if (health <= 0) {
                alive = false;
            }
        };

        void special_attack();
};
#endif
