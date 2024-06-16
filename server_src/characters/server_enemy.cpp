#include "server_enemy.h"

bool Enemy::contact_x(Character &ch) {
    if (right_side() != ch.left_side() || left_side() != ch.right_side() ||
        lower_side() > ch.upper_side() || upper_side() < ch.lower_side()) {
        return false;
    }
    ch.take_damage(damage);
    return true;
}

bool Enemy::contact_y(Character &ch) {
    if (lower_side() != ch.upper_side() || upper_side() != ch.lower_side() ||
          right_side() < ch.left_side() || left_side() > ch.right_side()) {
        return false;
    }
    ch.take_damage(damage);
    return true;
}

InfoEnemigo Enemy::set_data() {
    InfoEnemigo data(type, x_pos, y_pos, enemy_status);
    if (!alive) {
        enemy_status = EstadosEnemy::Death;
    }
    return data;
}

uint8_t Enemy::get_enemy_id() {
    return enemy_id;
}

uint8_t Enemy::get_damage() {
    return damage;
}

void Enemy::do_nothing() {
    enemy_status = EstadosEnemy::Idle;
}

void Enemy::move_x_pos(uint8_t &x) {
    enemy_status = EstadosEnemy::Move;
    x_pos += x;
}

void Enemy::move_y_pos(uint8_t &y) {
    enemy_status = EstadosEnemy::Move;
    y_pos += y;
}

bool Enemy::contact(Character &ch) {
    return contact_x(ch) || contact_y(ch);
}

void Enemy::take_damage(uint8_t &damage) {
    enemy_status = EstadosEnemy::Damaged;
    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
        respawn_time = respawn;
    }
}

void Enemy::revive() {
    //status = EstadosEnemy::Reviving;
    alive = true;
    health = full_health;
}
