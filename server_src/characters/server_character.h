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

#define HEALTH 100
#define POINTS 0

class Character {
    private:
        int player_id;

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

        int get_id();

        uint8_t left_side(); // Devuelve x_pos - hitbox_x

        uint8_t right_side(); // Devuelve x_pos + hitbox_x

        uint8_t upper_side(); // Devuelve y_pos + hitbox_y

        uint8_t lower_side(); // Devuelve y_pos - hitbox_y

        bool is_dead();

        bool is_frozen();

        bool is_intoxicated();

        void move(uint8_t x, uint8_t y);

        void move_x_pos(uint8_t &movement, uint8_t &direction);

        void jump();

        void fall();

        void attack();

        void special_attack();

        void pick_up_ammo();

        void change_weapon(Weapon new_weapon);

        void set_frozen_status(bool status);

        void set_intoxicated_status(bool status); // Convierte intoxicated a true/false

        void take_damage(uint8_t &damage); // health - damage

        void add_points(uint8_t &sum); // points + sum

        void revive();
};
#endif
