#ifndef SERVER_PLAYER_SPAZ_H_
#define SERVER_PLAYER_SPAZ_H_

#include "server_character.h"

#define HEALTH 100
#define POINTS 0
#define X_START 0
#define Y_START 0
#define X_HITBOX 5
#define Y_HITBOX 10
#define JUMP_HEIGHT 10

class PlayerSpaz : public Character {
    private:
        uint8_t health = HEALTH;

        Weapon weapon;

        uint8_t points = POINTS;

        uint8_t x_pos = X_START;

        uint8_t y_pos = Y_START;

        uint8_t x_hitbox = X_HITBOX;

        uint8_t y_hitbox = Y_HITBOX;

        bool alive = true;

        bool frozen = false;

        bool intoxicated = false;
    public:
        PlayerSpaz() : weapon(Blaster()) {};
        
        void special_attack();
};
#endif
