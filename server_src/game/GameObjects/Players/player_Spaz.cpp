#include "player_Spaz.h"

PlayerSpaz::PlayerSpaz(int id) : ObjectPlayer(id, TipoPlayer::Spaz) {

}

void PlayerSpaz::specialAttack() {
    if (is_dead() || is_intoxicated() || isJumping() ||
        is_falling() || estado == EstadosPlayer::SpecialAttack) {
        return;
    }
    isDoingSpecialAttack = true;
    estado = EstadosPlayer::SpecialAttack;
}


void PlayerSpaz::updateSpecialAttack() {
    timer_specialAttack++;
    if (timer_specialAttack >= TIME_SIDEKECK) {
        estado = EstadosPlayer::SpecialAttack;
        isDoingSpecialAttack = false;
        timer_specialAttack = 0;
    }
    else if (timer_specialAttack >= 8) { // tarda unos frames en arrancar
        if (move_x(direction, defaultRunSpeed)) {

        } else { //chocó con una pared

        }
    }
}
