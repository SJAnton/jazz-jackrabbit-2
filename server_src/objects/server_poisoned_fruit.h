#ifndef SERVER_POISONED_FRUIT_H_
#define SERVER_POISONED_FRUIT_H_

#include "server_object.h"

#define ITR_PER_SEC 15

class PoisonedFruit : public Object {
    private:

    public:
        PoisonedFruit(std::vector<uint8_t> &data) {
            type = FrutaEnvenenada;
            object_id = data[OBJ_ID_POS];
            amount = data[OBJ_AMOUNT_POS] * ITR_PER_SEC;
            xy_hitbox = data[OBJ_HITBOX_POS];
        }
};
#endif
