#ifndef SERVER_CHARACTER_H_
#define SERVER_CHARACTER_H_

#include <map>
#include <list>
#include <string>
#include <memory>
#include <vector>
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
#include "../../common_src/info_juego.h"
#include "../../common_src/constantes.h"

#define JAZZ_ID 1
#define LORI_ID 2
#define SPAZ_ID 3

#define HP_POS 0
#define PT_POS 1
#define XH_POS 2
#define YH_POS 3
#define JH_POS 4

class Character {
    private:
        int character_id; // Jazz = 1, Lori = 2, Spaz = 3

        EstadosPlayer status;

        TipoArma weapon_type = TipoArma::Blaster;

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

        InfoPlayer set_data(int id);

        int get_character_id();

        uint8_t get_x_pos();

        uint8_t get_y_pos();

        uint8_t left_side(); // Devuelve x_pos - hitbox_x

        uint8_t right_side(); // Devuelve x_pos + hitbox_x

        uint8_t upper_side(); // Devuelve y_pos + hitbox_y

        uint8_t lower_side(); // Devuelve y_pos - hitbox_y

        bool is_dead();

        bool is_frozen();

        bool is_intoxicated();

        void do_nothing();

        void move(uint8_t x, uint8_t y);

        void move_x_pos(uint8_t &movement, uint8_t &direction);

        void jump();

        void fall();

        void attack(uint8_t direction, std::list<std::shared_ptr<Projectile>> &projectile_list,
                    std::map<std::string, std::vector<uint8_t>> &data_map);

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
