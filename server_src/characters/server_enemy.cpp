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

void Enemy::move_x_pos(uint8_t &x) {
    x_pos += x;
}

void Enemy::move_y_pos(uint8_t &y) {
    y_pos += y;
}

bool Enemy::contact(Character &ch) {
    return contact_x(ch) || contact_y(ch);
}
