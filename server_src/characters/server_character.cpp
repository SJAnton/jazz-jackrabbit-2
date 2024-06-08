#include "server_character.h"

#define RUN_SPEED 3
#define LOW_HEALTH 20
#define FULL_HEALTH 100

#define WALK 0x12
#define RUN 0x13
#define LEFT 0x4C
#define RIGHT 0x52

#define BLASTERBALL_KEY "Blasterball"
#define BOUNCERBALL_KEY "Bouncerball"
#define ELECTROBALL_KEY "Electroball"
#define ICEBALL_KEY "Iceball"
#define FIREBALL_KEY "Fireball"
#define ROCKET_KEY "Rocket"
#define SEEKER_ROCKET_KEY "SeekerRocket"
#define TOASTERBALL_KEY "Toasterball"

#define BLASTER_ID 0x01
#define BOUNCER_ID 0x02
#define ELECTRO_BLASTER_ID 0x03
#define FREEZER_ID 0x04
#define PEPPER_SPRAY_ID 0x05
#define RF_MISSILE_ID 0x06
#define SEEKER_ID 0x07
#define TNT_ID 0x08
#define TOASTER_ID 0x09

InfoPlayer Character::set_data(int id) {
    InfoPlayer data(id, x_pos, y_pos, character_id, status, health,
                    points, weapon_type, weapon.get_ammo());
    if (!alive) {
        status = EstadosPlayer::Dead;
    }
    return data;
}

int Character::get_character_id() {
    return character_id;
}

uint8_t Character::get_x_pos() {
    return x_pos;
}

uint8_t Character::get_y_pos() {
    return y_pos;
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
                break;
            } else {
                status = EstadosPlayer::Running;
                x_pos -= RUN_SPEED;
                break;
            }
        case RIGHT:
            if (movement == WALK || (movement == RUN && intoxicated)) {
                if (intoxicated) {
                    status = EstadosPlayer::IntoxicatedWalk;
                } else {
                    status = EstadosPlayer::Walking;
                }
                x_pos++;
                break;
            } else {
                status = EstadosPlayer::Running;
                x_pos += RUN_SPEED;
                break;
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

#include <iostream>

void Character::attack(uint8_t direction, std::list<std::shared_ptr<Projectile>> &projectile_list,
                        std::map<std::string, std::vector<uint8_t>> &data_map) {
    std::cout << "id = " << (int)weapon.get_id() << std::endl;
    if (is_intoxicated() || is_dead() || !weapon.shoot()) {
        return;
    }
    uint8_t projectile_x;
    status = EstadosPlayer::Shooting;
    std::shared_ptr<Projectile> projectile;
    if (direction == LEFT) {
        projectile_x--;
    } else {
        projectile_x++;
    }
    switch (weapon.get_id()) {
        case BLASTER_ID:
            projectile = std::make_shared<Blasterball>(
                            projectile_x, y_pos, direction, data_map[BLASTERBALL_KEY]
            );
            break;
        case BOUNCER_ID:
            projectile = std::make_shared<Bouncerball>(
                            projectile_x, y_pos, direction, data_map[BOUNCERBALL_KEY]
            );
            break;
        case ELECTRO_BLASTER_ID:
            projectile = std::make_shared<Electroball>(
                            projectile_x, y_pos, direction, data_map[ELECTROBALL_KEY]
            );
            break;
        case FREEZER_ID:
            projectile = std::make_shared<Iceball>(
                            projectile_x, y_pos, direction, data_map[ICEBALL_KEY]
            );
            break;
        case PEPPER_SPRAY_ID:
            projectile = std::make_shared<Fireball>(
                            projectile_x, y_pos, direction, data_map[FIREBALL_KEY]
            );
            break;
        case RF_MISSILE_ID:
            projectile = std::make_shared<Rocket>(
                            projectile_x, y_pos, direction, data_map[ROCKET_KEY]
            );
            break;
        case SEEKER_ID:
            projectile = std::make_shared<SeekerRocket>(
                            projectile_x, y_pos, direction, data_map[SEEKER_ROCKET_KEY]
            );
            break;
        case TNT_ID:
            //projectile = std::make_shared<Projectile>();
            break;
        case TOASTER_ID:
            projectile = std::make_shared<Toasterball>(
                            projectile_x, y_pos, direction, data_map[TOASTERBALL_KEY]
            );
            break;
    }
    projectile_list.push_back(projectile);
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
        case SEEKER_ID:
            weapon_type = TipoArma::Seeker;
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
