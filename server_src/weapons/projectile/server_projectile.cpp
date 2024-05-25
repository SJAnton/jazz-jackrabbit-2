#include "server_projectile.h"

Projectile::Projectile() {}

/*
bool Projectile::contact_x(Character &ch) {
    if (right_side() != ch.left_side() || left_side() != ch.right_side() ||
        lower_side() > ch.upper_side() || upper_side() < ch.lower_side()) {
        // Si el hitbox derecho (o izquierdo) del proyectil no toca al hitbox
        // izquierdo (o derecho) del personaje, o el proyectil está más arriba
        // del hitbox superior del personaje, o más abajo del hitbox inferior,
        // no hay contacto
        return false;
    }
    // Para que haya contacto:
    // right_side() == ch.left_side() (o left_side() == ch.right_side())
    // upper_side() <= ch.upper_side() y lower_side() >= ch.lower_side()
    ch.take_damage(damage);
    return true;
}

bool Projectile::contact_y(Character &ch) {
    if (lower_side() != ch.upper_side() || upper_side() != ch.lower_side() ||
          right_side() < ch.left_side() || left_side() > ch.right_side()) {
        return false;
    }
    // Para que haya contacto:
    // lower_side() == ch.upper_side() (o upper_side() == ch.lower_side())
    // left_side() >= ch.left_side() y right_side() <= ch.right_side()
    ch.take_damage(damage);
    return true;
}*/

uint8_t Projectile::get_id() {
    return projectile_id;
}

uint8_t Projectile::left_side() {
    return x_pos - x_hitbox;
}

uint8_t Projectile::right_side() {
    return x_pos + x_hitbox;
}

uint8_t Projectile::upper_side() {
    return y_pos + y_hitbox;
}

uint8_t Projectile::lower_side() {
    return y_pos - y_hitbox;
}

bool Projectile::is_powered_up() {
    return powered_up;
}

void Projectile::move(uint8_t x, uint8_t y) {
    x_pos = x;
    y_pos = y;
}

void Projectile::move_x_pos(uint8_t &x) {
    x_pos += x;
}

void Projectile::move_y_pos(uint8_t &y) {
    y_pos += y;
}

void Projectile::power_up() {
    if (powered_up) {
        return;
    }
    powered_up = true;
    damage *= damage_multiplier;
}

void Projectile::power_up_end() {
    if (!powered_up) {
        return;
    }
    powered_up = false;
    damage /= damage_multiplier;
}

/*
bool Projectile::contact(Character &ch) {
    return contact_x(ch) || contact_y(ch);
}*/
