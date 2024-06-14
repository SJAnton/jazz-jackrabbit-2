#ifndef SERVER_CHARACTER_H_
#define SERVER_CHARACTER_H_

#include <map>
#include <list>
#include <string>
#include <memory>
#include <vector>
#include <cstdint>

#include "../objects/server_object.h"
#include "../objects/server_ammo.h"
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
#include "../../common_src/constantes_protocolo.h"

#define JAZZ_ID 1
#define LORI_ID 2
#define SPAZ_ID 3

#define HP_POS 0
#define PT_POS 1
#define XH_POS 2
#define YH_POS 3
#define JH_POS 4

#define AMMO_KEY "InitAmmo"
#define CHARACTER_KEY "Character"

#define MOVING_SPEED_POS 1
#define RUNNING_SPEED_POS 2

#define BOUNCER_AMMO_POS 0
#define ELECTRO_BLASTER_AMMO_POS 1
#define FREEZER_AMMO_POS 2
#define PEPPER_SPRAY_AMMO_POS 3
#define RF_MISSILE_AMMO_POS 4
#define SEEKER_AMMO_POS 5
#define TNT_AMMO_POS 6
#define TOASTER_AMMO_POS 7

#define RESPAWN_TIME_POS 0
#define ITR_PER_SEC 15

class Character {
    protected:
        int character_id; // Jazz = 1, Lori = 2, Spaz = 3

        EstadosPlayer status = EstadosPlayer::Inactive;

        TipoArma weapon_type;

        uint8_t health;

        uint8_t full_health;

        std::unique_ptr<Weapon> weapon;

        uint8_t points;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t x_hitbox;

        uint8_t y_hitbox;

        bool alive = true;

        bool frozen = false;

        uint8_t moving_speed;

        uint8_t running_speed;

        uint8_t intoxicated_time;

        uint8_t jump_height;

        uint8_t bouncer_ammo;

        uint8_t electro_blaster_ammo;

        uint8_t freezer_ammo;

        uint8_t pepper_spray_ammo;

        uint8_t rf_missile_ammo;

        uint8_t seeker_ammo;

        uint8_t tnt_ammo;

        uint8_t toaster_ammo;

        int respawn;

        int respawn_time = 0;

        int jump_left = 0;

        std::map<std::string, std::vector<uint8_t>> &map;

        void pick_up_ammo(std::shared_ptr<Object> &object);

        void add_points(uint8_t sum);

        void add_health(uint8_t health);

    public:
        Character(std::map<std::string, std::vector<uint8_t>> &map) : map(map) {
            std::vector<uint8_t> ammo_data = map[AMMO_KEY];

            full_health = health;
            moving_speed = map[CHARACTER_KEY][MOVING_SPEED_POS];
            running_speed = map[CHARACTER_KEY][RUNNING_SPEED_POS];

            // Cantidad inicial de munición
            bouncer_ammo = ammo_data[BOUNCER_AMMO_POS];
            electro_blaster_ammo = ammo_data[ELECTRO_BLASTER_AMMO_POS];;
            freezer_ammo = ammo_data[FREEZER_AMMO_POS];
            pepper_spray_ammo = ammo_data[PEPPER_SPRAY_AMMO_POS];
            rf_missile_ammo = ammo_data[RF_MISSILE_AMMO_POS];
            seeker_ammo = ammo_data[SEEKER_AMMO_POS];
            tnt_ammo = ammo_data[TNT_AMMO_POS];
            toaster_ammo = ammo_data[TOASTER_AMMO_POS];

            respawn = map[CHARACTER_KEY][RESPAWN_TIME_POS] * ITR_PER_SEC;
        };

        virtual ~Character() = default;

        InfoPlayer set_data(int id);

        int get_character_id();

        EstadosPlayer get_status();

        uint8_t get_points();

        uint8_t get_x_pos();

        uint8_t get_y_pos();

        uint8_t left_side(); // Devuelve x_pos - hitbox_x

        uint8_t right_side(); // Devuelve x_pos + hitbox_x

        uint8_t upper_side(); // Devuelve y_pos + hitbox_y

        uint8_t lower_side(); // Devuelve y_pos - hitbox_y

        bool is_dead();

        bool is_frozen();

        bool is_intoxicated();

        bool is_jumping();

        virtual void do_nothing();

        void move(uint8_t x, uint8_t y);

        void jump();

        void fall();

        virtual void special_attack();

        void set_frozen_status(bool status);

        void set_intoxicated_time(int time);

        virtual void take_damage(uint8_t &damage);

        void reduce_intoxicated_time();

        void reduce_respawn_time();

        virtual void revive();

        void move_x_pos(uint8_t &movement, uint8_t &direction);

        void attack(uint8_t direction, std::list<std::shared_ptr<Projectile>> &projectile_list,
                    std::map<std::string, std::vector<uint8_t>> &data_map);

        void change_weapon(int id);

        void pick_up_object(std::shared_ptr<Object> &object);
};
#endif
