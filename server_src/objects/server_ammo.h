#ifndef SERVER_AMMO_H_
#define SERVER_AMMO_H_

#include "server_object.h"
#include "../../common_src/constantes_protocolo.h"

#define AMMO_BOUNCER_AMMO_POS 1
#define AMMO_ELECTRO_BLASTER_AMMO_POS 2
#define AMMO_FREEZER_AMMO_POS 3
#define AMMO_PEPPER_SPRAY_AMMO_POS 3
#define AMMO_RF_MISSILE_AMMO_POS 4
#define AMMO_SEEKER_AMMO_POS 5
#define AMMO_TNT_AMMO_POS 6
#define AMMO_TOASTER_AMMO_POS 7
#define AMMO_HITBOX_POS 8

class Ammo : public Object {
    private:
        int ammo_id;

    public:
        Ammo(int id, std::vector<uint8_t> &data) {
            switch (id) {
                case BLASTER_ID:
                    // Munición infinita
                    break;
                case BOUNCER_ID:
                    amount = data[AMMO_BOUNCER_AMMO_POS];
                    break;
                case ELECTRO_BLASTER_ID:
                    amount = data[AMMO_ELECTRO_BLASTER_AMMO_POS];
                    break;
                case FREEZER_ID:
                    amount = data[AMMO_FREEZER_AMMO_POS];
                    break;
                case PEPPER_SPRAY_ID:
                    amount = data[AMMO_PEPPER_SPRAY_AMMO_POS];
                    break;
                case RF_MISSILE_ID:
                    amount = data[AMMO_RF_MISSILE_AMMO_POS];
                    break;
                case SEEKER_ID:
                    amount = data[AMMO_SEEKER_AMMO_POS];
                    break;
                case TNT_ID:
                    amount = data[AMMO_TNT_AMMO_POS];
                    break;
                case TOASTER_ID:
                    amount = data[AMMO_TOASTER_AMMO_POS];
                    break;
                default:
                    throw std::invalid_argument("Invalid ammo ID");
            }
            ammo_id = id;
            type = Municion;
            object_id = data[OBJ_ID_POS];
            xy_hitbox = data[OBJ_HITBOX_POS];
        }

        Ammo(uint8_t id, uint8_t x, uint8_t y, uint8_t am_amount, uint8_t hitbox, uint8_t am_id) {
            // Para construir un objecto Ammo leído de un mapa
            object_id = id;
            x_pos = x;
            y_pos = y;
            amount = am_amount;
            xy_hitbox = hitbox;
            ammo_id = am_id;
            type = Municion;
        }

        int get_id();
};
#endif
