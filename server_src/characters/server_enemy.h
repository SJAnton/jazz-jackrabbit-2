#ifndef SERVER_ENEMY_H_
#define SERVER_ENEMY_H_

#include <vector>
#include <cstdint>

#include "server_character.h"

#define BAT_KEY "EnemyBat"
#define LIZARD_KEY "EnemyLizard"
#define RAT_KEY "EnemyRat"

class Enemy : public Character {
    private:
        bool contact_x(Character &ch);

        bool contact_y(Character &ch);

    protected:
        uint8_t damage;
        
    public:
        Enemy(std::map<std::string, std::vector<uint8_t>> &map) : Character(map) {};

        void move_x_pos(uint8_t &x);

        void move_y_pos(uint8_t &y);

        bool contact(Character &ch);
};
#endif
