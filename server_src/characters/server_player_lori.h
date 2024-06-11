#ifndef SERVER_PLAYER_LORI_H_
#define SERVER_PLAYER_LORI_H_

#include "server_character.h"

#define LORI_KEY "PlayerLori"
#define BLASTER_KEY "Blaster"

class PlayerLori : public Character {
    private:
        
    public:
        PlayerLori(uint8_t x, uint8_t y, std::map<std::string, std::vector<uint8_t>> &map) :
                    Character(map) {
            std::vector<uint8_t> data = map[LORI_KEY];
            x_pos = x;
            y_pos = y;
            character_id = LORI_ID;
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

        void special_attack();
};
#endif
