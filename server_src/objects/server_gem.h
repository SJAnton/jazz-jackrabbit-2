#ifndef SERVER_GEM_H_
#define SERVER_GEM_H_

#include "server_object.h"

class Gem : public Object {
    private:

    public:
        Gem(std::vector<uint8_t> &data) {
            type = Diamante;
            object_id = data[OBJ_ID_POS];
            amount = data[OBJ_AMOUNT_POS];
            xy_hitbox = data[OBJ_HITBOX_POS];
        }
};
#endif
