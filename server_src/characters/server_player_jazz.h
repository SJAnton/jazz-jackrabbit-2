#ifndef SERVER_PLAYER_JAZZ_H_
#define SERVER_PLAYER_JAZZ_H_

#include "server_character.h"

#define JAZZ_KEY "PlayerJazz"
#define BLASTER_KEY "Blaster"

#define X_START 0
#define Y_START 0

class PlayerJazz : public Character {
    private:
        
    public:
        PlayerJazz(uint8_t x, uint8_t y, std::map<std::string, std::vector<uint8_t>> &map) {
            std::vector<uint8_t> data = map[JAZZ_KEY];
            x_pos = x;
            y_pos = y;
            character_id = JAZZ_ID;
            health = data[HP_POS];
            weapon = std::make_unique<Blaster>(map[BLASTER_KEY]);
            weapon_type = TipoArma::Blaster;
            points = data[PT_POS];
            x_hitbox = data[XH_POS];
            y_hitbox = data[YH_POS];
            jump_height = data[JH_POS];
            if (health <= 0) {
                alive = false;
            }
        };

        void special_attack() override;
};
#endif
