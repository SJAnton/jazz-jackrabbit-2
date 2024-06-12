#ifndef SERVER_COIN_H_
#define SERVER_COIN_H_

#include "server_object.h"

class Coin : public Object {
    private:

    public:
        Coin(std::vector<uint8_t> &data) {
            type = Moneda;
            object_id = data[OBJ_ID_POS];
            amount = data[OBJ_AMOUNT_POS];
            xy_hitbox = data[OBJ_HITBOX_POS];
        }
};
#endif
