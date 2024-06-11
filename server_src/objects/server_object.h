#ifndef SERVER_OBJECT_H_
#define SERVER_OBJECT_H_

#include <vector>
#include <cstdint>
#include <stdexcept>

#define OBJ_ID_POS 0
#define OBJ_AMOUNT_POS 1
#define OBJ_HITBOX_POS 2

class Object {
    protected:
        uint8_t object_id;

        uint8_t x_pos;

        uint8_t y_pos;

        uint8_t amount;

        uint8_t xy_hitbox;

    public:
        Object() {};

        virtual ~Object() = default;

        uint8_t get_object_id();

        uint8_t get_x_pos();

        uint8_t get_y_pos();

        uint8_t get_amount();

        uint8_t left_side();

        uint8_t right_side();

        uint8_t upper_side();

        uint8_t lower_side();
};
#endif
