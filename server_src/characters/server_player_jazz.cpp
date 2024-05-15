#include "server_player_jazz.h"

#define RUN_SPEED 3

#define MOV_LEFT 0x12
#define MOV_RIGHT 0x13
#define RUN_LEFT 0x14
#define RUN_RIGHT 0x15

uint8_t PlayerJazz::left_side() {
    return x_pos - x_hitbox;
}

uint8_t PlayerJazz::right_side() {
    return x_pos + x_hitbox;
}

uint8_t PlayerJazz::upper_side() {
    return y_pos + y_hitbox;
}

uint8_t PlayerJazz::lower_side() {
    return y_pos - y_hitbox;
}

bool PlayerJazz::is_dead() {
    return !alive;
}

void PlayerJazz::move(uint8_t x, uint8_t y) {
    x_pos = x;
    y_pos = y;
}

void PlayerJazz::attack() {
    weapon.shoot();
}

void PlayerJazz::pick_up_ammo() {

}

void PlayerJazz::change_weapon(Weapon new_weapon) {
    weapon = new_weapon;
} 

void PlayerJazz::set_intoxicated_status(bool status) {
    intoxicated = status;
}

void PlayerJazz::take_damage(uint8_t damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

void PlayerJazz::add_points(uint8_t sum) {
    if (points < 0) {
        return;
    }
    points += sum;
}

void PlayerJazz::move_x_pos(uint8_t movement) {
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

void PlayerJazz::jump() {
    y_pos++;
}

void PlayerJazz::fall() {
    y_pos--;
}

void PlayerJazz::revive() {
    alive = true;
    health = HEALTH;
}
