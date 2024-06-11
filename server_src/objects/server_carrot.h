#ifndef SERVER_CARROT_H_
#define SERVER_CARROT_H_

#include "server_object.h"

class Carrot : public Object {
    private:

    public:
        Carrot(std::vector<uint8_t> &data) {
            object_id = data[OBJ_ID_POS];
            amount = data[OBJ_AMOUNT_POS]; // Cantidad de vida que restaura
            xy_hitbox = data[OBJ_HITBOX_POS];
        }
};
#endif
