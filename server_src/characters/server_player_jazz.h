#ifndef SERVER_PLAYER_JAZZ_H_
#define SERVER_PLAYER_JAZZ_H_

#include "server_character.h"

#define JAZZ_KEY "PlayerJazz"
#define BLASTER_KEY "Blaster"

#define X_START 0
#define Y_START 0

class PlayerJazz : public Character {
    private:
        int character_id = JAZZ_ID;

        uint8_t health;

        uint8_t full_health;

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
        PlayerJazz(std::map<std::string, std::vector<uint8_t>> &map)
                    : weapon(Blaster(map[BLASTER_KEY])) {
            std::vector<uint8_t> data = map[JAZZ_KEY];
            health = data[HP_POS];
            points = data[PT_POS];
            x_hitbox = data[XH_POS];
            y_hitbox = data[YH_POS];
            jump_height = data[JH_POS];
            if (health <= 0) {
                alive = false;
            }
        };

        int get_character_id();

        void special_attack();
};
#endif
