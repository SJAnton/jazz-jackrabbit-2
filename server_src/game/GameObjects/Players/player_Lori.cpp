#include "player_Lori.h"

PlayerLori::PlayerLori(int id) : ObjectPlayer(id, TipoPlayer::Lori) {

}

void PlayerLori::specialAttack() {
    if (is_dead() || is_intoxicated() || isJumping() ||
        is_falling() || estado == EstadosPlayer::SpecialAttack) {
        return;
    }
    isDoingSpecialAttack = true;
    tocandoSuelo = false;
    estado = EstadosPlayer::SpecialAttack;

}

void PlayerLori::updateSpecialAttack() {
    timer_specialAttack++;
    if (timer_specialAttack >= TIME_HIGHKICK) {
        estado = EstadosPlayer::SpecialAttack;
        isDoingSpecialAttack = false;
        timer_specialAttack = 0;
    }
    else if (timer_specialAttack >= 4) { // tarda unos frames en arrancar
        if (timer_specialAttack <= TIME_HIGHKICK/2) {
            if (move_y(defaultRunSpeed)) {

            } else { //chocó con una pared

            }
        } else {
            down_y(defaultRunSpeed);
        }
        
    }
}
