#include "server_player.h"

#define MOV_LEFT 0x12
#define MOV_RIGHT 0x13
#define RUN_LEFT 0x14
#define RUN_RIGHT 0x15

uint8_t Player::get_health() {
    return health;
}

uint8_t Player::get_x_pos() {
    return x_pos;
}

uint8_t Player::get_y_pos() {
    return y_pos;
}

uint8_t Player::get_left_side() {
    return x_pos - x_hitbox;
}

uint8_t Player::get_right_side() {
    return x_pos + x_hitbox;
}

uint8_t Player::get_upper_side() {
    return y_pos + y_hitbox;
}

uint8_t Player::get_lower_side() {
    return y_pos - y_hitbox;
}

void Player::set_health(uint8_t new_health) {
    if (new_health < 0) {
        health = 0;
    } else {
        health = new_health;
    }
}

void Player::set_x_pos(uint8_t new_x_pos) {
    x_pos = new_x_pos;
}

void Player::set_y_pos(uint8_t new_y_pos) {
    y_pos = new_y_pos;
}

void Player::set_intoxicated_status(bool status) {
    intoxicated = status;
}

void Player::take_damage(uint8_t damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

void Player::add_points(uint8_t sum) {
    points += sum;
}

void Player::move_x_pos(uint8_t movement) {
    switch (movement) {
        case MOV_LEFT:

        case MOV_RIGHT:

        case RUN_LEFT:

        case RUN_RIGHT:

        default:

    }
}

void Player::jump() {
    for (y_pos; y_pos <= JUMP_HEIGHT; y_pos++) {

    }
    fall();
}

void Player::fall() {

}

void Player::revive() {
    health = HEALTH;
}
