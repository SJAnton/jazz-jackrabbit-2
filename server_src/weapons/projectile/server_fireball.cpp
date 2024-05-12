#include "server_fireball.h"

void Fireball::move_x_pos(uint8_t &x) {
    for (x_pos; x_pos <= x; x_pos++) {

    }
}

void Fireball::move_y_pos(uint8_t &y) {
    for (y_pos; y_pos <= y; y_pos++) {
        
    }
}

void Fireball::powerup() {
    damage *= DMG_MULTIPLIER;
}

void Fireball::powerup_end() {
    damage /= DMG_MULTIPLIER;
}

bool Fireball::contact() {
    /*  El hitbox_x derecho (o izquierdo) debe estar en la misma posición
     *  que el hitbox_x izquierdo (o derecho) del enemigo, y debe estar
     *  entre su hitbox_y superior e inferior para hacer contacto */
    return true;
}
