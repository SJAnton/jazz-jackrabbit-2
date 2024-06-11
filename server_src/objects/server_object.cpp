#include "server_object.h"

uint8_t Object::get_object_id() {
    return object_id;
}

uint8_t Object::get_x_pos() {
    return x_pos;
}

uint8_t Object::get_y_pos() {
    return y_pos;
}

uint8_t Object::get_amount() {
    return amount;
}

uint8_t Object::left_side() {
    return x_pos - xy_hitbox;
}

uint8_t Object::right_side() {
    return x_pos + xy_hitbox;
}

uint8_t Object::upper_side() {
    return y_pos + xy_hitbox;
}

uint8_t Object::lower_side() {
    return y_pos - xy_hitbox;
}
