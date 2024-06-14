#ifndef SERVER_OBJECT_H_
#define SERVER_OBJECT_H_

#include <vector>
#include <cstdint>
#include <stdexcept>

#include "../../common_src/info_juego.h"

#define OBJ_ID_POS 0
#define OBJ_AMOUNT_POS 1
#define OBJ_HITBOX_POS 2

#define CARROT_ID 2
#define COIN_ID 3
#define GEM_ID 4
#define POISONED_FRUIT_ID 5

class Object {
    protected:
        uint8_t object_id;

        TipoRecolectable type;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t amount;

        uint8_t xy_hitbox;

    public:
        Object() {};

        Object(uint8_t id, uint8_t x, uint8_t y, uint8_t amount, uint8_t hitbox) :
                object_id(id), x_pos(x), y_pos(y), amount(amount), xy_hitbox(hitbox) {
                    // Para construir un objecto leído de un mapa
                    switch (id) {
                        case CARROT_ID:
                            type = Zanahoria;
                            break;
                        case COIN_ID:
                            type = Moneda;
                            break;
                        case GEM_ID:
                            type = Diamante;
                            break;
                        case POISONED_FRUIT_ID:
                            type = FrutaEnvenenada;
                            break;
                    }
                }

        virtual ~Object() = default;

        InfoRecolectable set_data();

        uint8_t get_object_id();

        uint8_t get_x_pos();

        uint8_t get_y_pos();

        uint8_t get_hitbox();

        uint8_t get_amount();

        uint8_t left_side();

        uint8_t right_side();

        uint8_t upper_side();

        uint8_t lower_side();
};
#endif
