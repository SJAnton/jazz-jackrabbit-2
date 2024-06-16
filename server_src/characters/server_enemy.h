#ifndef SERVER_ENEMY_H_
#define SERVER_ENEMY_H_

#include <vector>
#include <cstdint>

#include "server_character.h"
#include "../../common_src/info_juego.h"

#define BAT_KEY "EnemyBat"
#define LIZARD_KEY "EnemyLizard"
#define RAT_KEY "EnemyRat"

#define BAT_ID 0x01
#define LIZARD_ID 0x02
#define RAT_ID 0x03

#define H_POS 0
#define D_POS 1
#define XH_POS 2
#define YH_POS 3

class Enemy : public Character {
    private:
        bool contact_x(Character &ch);

        bool contact_y(Character &ch);

    protected:
        uint8_t enemy_id;

        uint8_t damage;

        TipoEnemy type;

        EstadosEnemy enemy_status;
        
    public:
        Enemy(std::map<std::string, std::vector<uint8_t>> &map) : Character(map) {};

        Enemy(uint8_t x, uint8_t y, uint8_t hp, uint8_t id,
                uint8_t dmg, uint8_t x_hbx, uint8_t y_hbx) {
            x_pos = x;
            y_pos = y;
            health = hp;
            enemy_id = id;
            damage = dmg;
            x_hitbox = x_hbx;
            y_hitbox = y_hbx;
        }

        uint8_t get_enemy_id();

        uint8_t get_damage();

        InfoEnemigo set_data();

        void do_nothing() override;

        void move_x_pos(uint8_t &x);

        void move_y_pos(uint8_t &y);

        bool contact(Character &ch);

        void take_damage(uint8_t &damage) override;

        void revive() override;
};
#endif
