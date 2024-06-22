#include "player_Jazz.h"

PlayerJazz::PlayerJazz(int id) : ObjectPlayer(id, TipoPlayer::Jazz) {

}

void PlayerJazz::specialAttack() {
    isDoingSpecialAttack = true;
    tocandoSuelo = false;
    estado = EstadosPlayer::SpecialAttack;
}


void PlayerJazz::updateSpecialAttack() {
    timer_specialAttack++;
    if (timer_specialAttack >= TIME_UPPERCUT) {
        isDoingSpecialAttack = false;
        timer_specialAttack = 0;
    }
    else if (timer_specialAttack >= 6) { // tarda unos frames en arrancar
        if (move_y(defaultRunSpeed-2)) {

        } else { //chocó con una pared

        }
    }
}
