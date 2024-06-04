#include "server_character.h"

#define RUN_SPEED 3
#define LOW_HEALTH 20
#define FULL_HEALTH 100

#define WALK 0x12
#define RUN 0x13
#define LEFT 0x4C
#define RIGHT 0x52

#define BLASTER_ID 0x01
#define BOUNCER_ID 0x02
#define ELECTRO_BLASTER_ID 0x03
#define FREEZER_ID 0x04
#define PEPPER_SPRAY_ID 0x05
#define RF_MISSILE_ID 0x06
#define TNT_ID 0x07
#define TOASTER_ID 0x08

InfoPlayer Character::set_data(int id) {
    InfoPlayer data(id, x_pos, y_pos, status, health, points, weapon_type, weapon.get_ammo());
    if (!alive) {
        status = EstadosPlayer::Dead;
    }
    return data;
}

int Character::get_id() {
    return player_id;
}

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

void Character::do_nothing() {
    if (health <= LOW_HEALTH) {
        status = EstadosPlayer::Dying;
    } else if (is_dead()) {
        status = EstadosPlayer::Dead;
    } else {
        status = EstadosPlayer::Inactive;
    }
}

void Character::move(uint8_t x, uint8_t y) {
    x_pos = x;
    y_pos = y;
    do_nothing();
}

void Character::move_x_pos(uint8_t &movement, uint8_t &direction) {
    if (is_frozen() || is_dead()) {
        return;
    }
    switch (direction) {
        case LEFT:
            if (movement == WALK || (movement == RUN && intoxicated)) {
                if (intoxicated) {
                    status = EstadosPlayer::IntoxicatedWalk;
                } else {
                    status = EstadosPlayer::Walking;
                }
                x_pos--;
            } else {
                status = EstadosPlayer::Running;
                x_pos -= RUN_SPEED;
            }
        case RIGHT:
            if (movement == WALK || (movement == RUN && intoxicated)) {
                if (intoxicated) {
                    status = EstadosPlayer::IntoxicatedWalk;
                } else {
                    status = EstadosPlayer::Walking;
                }
                x_pos++;
            } else {
                status = EstadosPlayer::Running;
                x_pos += RUN_SPEED;
            }
        default:
            return;
    }
}

void Character::jump() {
    if (is_frozen() || is_dead()) {
        return;
    }
    status = EstadosPlayer::Jumping;
    y_pos++;
}

void Character::fall() {
    if (is_dead()) {
        return;
    }
    status = EstadosPlayer::Falling;
    y_pos--;
}

void Character::attack() {
    if (is_intoxicated() || is_dead()) {
        return;
    }
    status = EstadosPlayer::Shooting;
    weapon.shoot();
}

void Character::special_attack() {
    if (is_frozen() || is_intoxicated() || is_dead()) {
        return;
    }
    status = EstadosPlayer::SpecialAttack;
}

void Character::pick_up_ammo() {

}

void Character::change_weapon(Weapon new_weapon) {
    switch (new_weapon.get_id()) {
        case BLASTER_ID:
            weapon_type = TipoArma::Blaster;
            break;
        case BOUNCER_ID:
            weapon_type = TipoArma::Bouncer;
            break;
        case ELECTRO_BLASTER_ID:
            weapon_type = TipoArma::ElectroBlaster;
            break;
        case FREEZER_ID:
            weapon_type = TipoArma::Freezer;
            break;
        case PEPPER_SPRAY_ID:
            weapon_type = TipoArma::PepperSpray;
            break;
        case RF_MISSILE_ID:
            weapon_type = TipoArma::RFMissile;
            break;
        case TNT_ID:
            weapon_type = TipoArma::TNT;
            break;
        case TOASTER_ID:
            weapon_type = TipoArma::Toaster;
            break;
    }
    weapon = new_weapon;
} 

void Character::set_frozen_status(bool status) {
    frozen = status;
}

void Character::set_intoxicated_status(bool status) {
    intoxicated = status;
}

void Character::take_damage(uint8_t &damage) {
    status = EstadosPlayer::Damaged;
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
    status = EstadosPlayer::Reviving;
    alive = true;
    health = FULL_HEALTH;
}
