#include "server_rocket.h"

void Rocket::move_x_pos(uint8_t &x) {
    for (x_pos; x_pos <= x; x_pos++) {

    }
}

void Rocket::move_y_pos(uint8_t &y) {
    for (y_pos; y_pos <= y; y_pos++) {
        
    }
}

void Rocket::powerup() {
    damage *= DMG_MULTIPLIER;
}

void Rocket::powerup_end() {
    damage /= DMG_MULTIPLIER;
}

bool Rocket::contact() {
    /*  El hitbox_x derecho (o izquierdo) debe estar en la misma posición
     *  que el hitbox_x izquierdo (o derecho) del enemigo, y debe estar
     *  entre su hitbox_y superior e inferior para hacer contacto */
    return true;
}
