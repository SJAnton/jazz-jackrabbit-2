#ifndef SERVER_PLAYER_LORI_H_
#define SERVER_PLAYER_LORI_H_

#include "server_character.h"

#define HEALTH 100
#define POINTS 0
#define X_START 0
#define Y_START 0
#define X_HITBOX 5
#define Y_HITBOX 10
#define JUMP_HEIGHT 10

class PlayerLori : public Character {
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
        PlayerLori() : weapon(Blaster()) {};
        
        uint8_t left_side(); // Devuelve x_pos - hitbox_x

        uint8_t right_side(); // Devuelve x_pos + hitbox_x

        uint8_t upper_side(); // Devuelve y_pos + hitbox_y

        uint8_t lower_side(); // Devuelve y_pos - hitbox_y

        bool is_dead();

        void move(uint8_t x, uint8_t y);

        void attack();

        void pick_up_ammo();

        void change_weapon(Weapon new_weapon);

        void set_intoxicated_status(bool status); // Convierte intoxicated a true/false

        void take_damage(uint8_t damage); // health - damage

        void add_points(uint8_t sum); // points + sum

        void move_x_pos(uint8_t movement); // Toma el byte de movimiento izq/der

        void jump();

        void fall(); // Caer hasta hacer contacto con el suelo

        void revive();
};
#endif
