#include "server_player_lori.h"

#define RUN_SPEED 3

#define MOV_LEFT 0x12
#define MOV_RIGHT 0x13
#define RUN_LEFT 0x14
#define RUN_RIGHT 0x15

uint8_t PlayerLori::left_side() {
    return x_pos - x_hitbox;
}

uint8_t PlayerLori::right_side() {
    return x_pos + x_hitbox;
}

uint8_t PlayerLori::upper_side() {
    return y_pos + y_hitbox;
}

uint8_t PlayerLori::lower_side() {
    return y_pos - y_hitbox;
}

bool PlayerLori::is_dead() {
    return !alive;
}

void PlayerLori::move(uint8_t x, uint8_t y) {
    x_pos = x;
    y_pos = y;
}

void PlayerLori::attack() {
    weapon.shoot();
}

void PlayerLori::pick_up_ammo() {

}

void PlayerLori::change_weapon(Weapon new_weapon) {
    weapon = new_weapon;
} 

void PlayerLori::set_intoxicated_status(bool status) {
    intoxicated = status;
}

void PlayerLori::take_damage(uint8_t damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

void PlayerLori::add_points(uint8_t sum) {
    if (points < 0) {
        return;
    }
    points += sum;
}

void PlayerLori::move_x_pos(uint8_t movement) {
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

void PlayerLori::jump() {
    y_pos++;
}

void PlayerLori::fall() {
    y_pos--;
}

void PlayerLori::revive() {
    alive = true;
    health = HEALTH;
}