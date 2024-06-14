#include "server_character.h"

#define RUN_SPEED 3
#define LOW_HEALTH 20

#define AMMO_ID 1
#define CARROT_ID 2
#define COIN_ID 3
#define GEM_ID 4
#define POISONED_FRUIT_ID 5

#define BLASTER_KEY "Blaster"
#define BOUNCER_KEY "Bouncer"
#define ELECTRO_BLASTER_KEY "ElectroBlaster"
#define FREEZER_KEY "Freezer"
#define PEPPER_SPRAY_KEY "PepperSpray"
#define RF_MISSILE_KEY "RFMissile"
#define SEEKER_KEY "Seeker"
#define TNT_KEY "TNT"
#define TOASTER_KEY "Toaster"

#define BLASTERBALL_KEY "Blasterball"
#define BOUNCERBALL_KEY "Bouncerball"
#define ELECTROBALL_KEY "Electroball"
#define ICEBALL_KEY "Iceball"
#define FIREBALL_KEY "Fireball"
#define ROCKET_KEY "Rocket"
#define SEEKER_ROCKET_KEY "SeekerRocket"
#define TOASTERBALL_KEY "Toasterball"

InfoPlayer Character::set_data(int id) {
    InfoPlayer data(id, x_pos, y_pos, character_id, status, health,
                    points, weapon_type, weapon->get_ammo());
    if (!alive) {
        status = EstadosPlayer::Dead;
    }
    return data;
}

int Character::get_character_id() {
    return character_id;
}

EstadosPlayer Character::get_status() {
    return status;
}

uint8_t Character::get_points() {
    return points;
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
    return intoxicated_time > 0;
}

bool Character::is_jumping() {
    return jump_left > 0;
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

void Character::jump() {
    if (is_frozen() || is_dead()) {
        return;
    } else if (jump_left == 0) {
        // Jump_left = veces que sube en el eje Y por iteración
        status = EstadosPlayer::Jumping;
        jump_left = jump_height;
    }
    y_pos++;
    jump_left--;
}

void Character::fall() {
    // TODO: return si está sobre un tile sólido
    if (is_dead() || is_jumping() || y_pos == 0) {
        return;
    }
    status = EstadosPlayer::Falling;
    y_pos--;
}

void Character::special_attack() {
    if (is_frozen() || is_intoxicated() || is_dead()) {
        return;
    }
    status = EstadosPlayer::SpecialAttack;
}

void Character::set_frozen_status(bool status) {
    frozen = status;
}

void Character::set_intoxicated_time(int time) {
    intoxicated_time = time;
}

void Character::take_damage(uint8_t &damage) {
    status = EstadosPlayer::Damaged;
    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
        respawn_time = respawn;
    }
}

void Character::add_points(uint8_t sum) {
    points += sum;
}

void Character::add_health(uint8_t sum) {
    health += sum;
    if (health > full_health) {
        health = full_health;
    }
}

void Character::reduce_intoxicated_time() {
    if (intoxicated_time == 0) {
        return;
    }
    intoxicated_time--;
}

void Character::reduce_respawn_time() {
    if (respawn_time == 0) {
        revive();
        return;
    }
    respawn_time--;
}

void Character::revive() {
    status = EstadosPlayer::Reviving;
    alive = true;
    health = full_health;
}

void Character::move_x_pos(uint8_t &movement, uint8_t &direction) {
    if (is_frozen() || is_dead()) {
        return;
    }
    switch (direction) {
        case LEFT:
            // Si está intoxicado no puede correr
            if (movement == ACTION_WALK || (movement == ACTION_RUN && is_intoxicated())) {
                if (is_intoxicated()) {
                    status = EstadosPlayer::IntoxicatedWalk;
                } else {
                    status = EstadosPlayer::Walking;
                }
                x_pos -= moving_speed;
                break;
            } else {
                status = EstadosPlayer::Running;
                x_pos -= running_speed;
                break;
            }
        case RIGHT:
            if (movement == ACTION_WALK || (movement == ACTION_RUN && is_intoxicated())) {
                if (is_intoxicated()) {
                    status = EstadosPlayer::IntoxicatedWalk;
                } else {
                    status = EstadosPlayer::Walking;
                }
                x_pos += moving_speed;
                break;
            } else {
                status = EstadosPlayer::Running;
                x_pos += running_speed;
                break;
            }
        default:
            return;
    }
}

void Character::attack(uint8_t direction, std::list<std::shared_ptr<Projectile>> &projectile_list,
                        std::map<std::string, std::vector<uint8_t>> &data_map) {
    if (is_intoxicated() || is_dead() || !weapon->shoot()) {
        return;
    }
    uint8_t projectile_x;
    status = EstadosPlayer::Shooting;
    std::shared_ptr<Projectile> projectile;
    // El proyectil comienza una dirección a la izquierda o a la derecha del personaje
    if (direction == LEFT) {
        projectile_x = left_side();
    } else {
        projectile_x = right_side();
    }
    switch (weapon->get_id()) {
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

void Character::pick_up_ammo(std::shared_ptr<Object> &object) {
    std::shared_ptr<Ammo> ammo = std::dynamic_pointer_cast<Ammo>(object);
    if (ammo == nullptr) {
        return;
    }
    switch (ammo->get_id()) {
        case BLASTER_ID:
            break;
        case BOUNCER_ID:
            bouncer_ammo += ammo->get_amount();
            break;
        case ELECTRO_BLASTER_ID:
            electro_blaster_ammo += ammo->get_amount();
            break;
        case FREEZER_ID:
            freezer_ammo += ammo->get_amount();
            break;
        case PEPPER_SPRAY_ID:
            pepper_spray_ammo += ammo->get_amount();
            break;
        case RF_MISSILE_ID:
            rf_missile_ammo += ammo->get_amount();
            break;
        case SEEKER_ID:
            seeker_ammo += ammo->get_amount();
            break;
        case TNT_ID:
            tnt_ammo += ammo->get_amount();
            break;
        case TOASTER_ID:
            toaster_ammo += ammo->get_amount();
            break;
        default:
            std::invalid_argument("Invalid ammo ID");
    }
}

void Character::change_weapon(int id) {
    std::unique_ptr<Weapon> new_weapon;
    switch (id) {
        case BLASTER_ID:
            weapon_type = TipoArma::Blaster;
            break;
        case BOUNCER_ID:
            weapon_type = TipoArma::Bouncer;
            new_weapon = std::make_unique<Bouncer>(bouncer_ammo, map[BOUNCER_KEY]);
            break;
        case ELECTRO_BLASTER_ID:
            weapon_type = TipoArma::ElectroBlaster;
            new_weapon = std::make_unique<ElectroBlaster>(
                                electro_blaster_ammo, map[ELECTRO_BLASTER_KEY]
                            );
            break;
        case FREEZER_ID:
            weapon_type = TipoArma::Freezer;
            new_weapon = std::make_unique<Freezer>(freezer_ammo, map[FREEZER_KEY]);
            break;
        case PEPPER_SPRAY_ID:
            weapon_type = TipoArma::PepperSpray;
            new_weapon = std::make_unique<PepperSpray>(pepper_spray_ammo, map[PEPPER_SPRAY_KEY]);
            break;
        case RF_MISSILE_ID:
            weapon_type = TipoArma::RFMissile;
            new_weapon = std::make_unique<RFMissile>(rf_missile_ammo, map[RF_MISSILE_KEY]);
            break;
        case SEEKER_ID:
            weapon_type = TipoArma::Seeker;
            new_weapon = std::make_unique<Seeker>(seeker_ammo, map[SEEKER_KEY]);
            break;
        case TNT_ID:
            weapon_type = TipoArma::TNT;
            new_weapon = std::make_unique<TNT>(tnt_ammo, map[TNT_KEY]);
            break;
        case TOASTER_ID:
            weapon_type = TipoArma::Toaster;
            new_weapon = std::make_unique<Toaster>(toaster_ammo, map[TOASTER_KEY]);
            break;
    }
    weapon.swap(new_weapon);
} 

void Character::pick_up_object(std::shared_ptr<Object> &object) {
    switch (object->get_object_id()) {
        case AMMO_ID:
            pick_up_ammo(object);
            break;
        case CARROT_ID:
            add_health(object->get_amount());
            break;
        case COIN_ID:
            add_points(object->get_amount());
            break;    
        case GEM_ID:
            add_points(object->get_amount());
            break;
        case POISONED_FRUIT_ID:
            set_intoxicated_time(object->get_amount());
            break;
    }
}
