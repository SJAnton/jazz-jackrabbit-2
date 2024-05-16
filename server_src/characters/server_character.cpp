#include "server_character.h"

#define RUN_SPEED 3

#define MOV_LEFT 0x12
#define MOV_RIGHT 0x13
#define RUN_LEFT 0x14
#define RUN_RIGHT 0x15

uint8_t Character::left_side() {
    return x_pos - x_hitbox;
}

uint8_t Character::right_side() {
    return x_pos + x_hitbox;
}

uint8_t Character::upper_side() {
    return y_pos + y_hitbox;
}

uint8_t Character::lower_side() {
    return y_pos - y_hitbox;
}

bool Character::is_dead() {
    return !alive;
}

bool Character::is_frozen() {
    return frozen;
}

bool Character::is_intoxicated() {
    return intoxicated;
}

void Character::move(uint8_t x, uint8_t y) {
    x_pos = x;
    y_pos = y;
}

void Character::move_x_pos(uint8_t &movement) {
    if (is_frozen()) {
        return;
    }
    switch (movement) {
        case MOV_LEFT:
            x_pos--;
        case MOV_RIGHT:
            x_pos++;
        case RUN_LEFT:
            x_pos -= RUN_SPEED;
        case RUN_RIGHT:
            x_pos += RUN_SPEED;
        default:
            return;
    }
}

void Character::jump() {
    if (is_frozen()) {
        return;
    }
    y_pos++;
}

void Character::fall() {
    y_pos--;
}

void Character::attack() {
    if (is_intoxicated()) {
        return;
    }
    weapon.shoot();
}

void Character::pick_up_ammo() {

}

void Character::change_weapon(Weapon new_weapon) {
    weapon = new_weapon;
} 

void Character::set_frozen_status(bool status) {
    frozen = status;
}

void Character::set_intoxicated_status(bool status) {
    intoxicated = status;
}

void Character::take_damage(uint8_t &damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

void Character::add_points(uint8_t &sum) {
    points += sum;
}

void Character::revive() {
    alive = true;
    health = HEALTH;
}
