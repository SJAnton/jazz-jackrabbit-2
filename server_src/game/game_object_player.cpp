#include "game_object_player.h"
#include <iostream>


#include "game_mundo.h"

ObjectPlayer::ObjectPlayer(int id, TipoPlayer &tipo, const Weapon &weapon) :
    GameObject(WIDTH_PLAYER, HEIGHT_PLAYER),
    id(id), 
    tipoPlayer(tipo),
    weapon(weapon)   
{
    type = TypeGameObject::Player;
}



// Movimientos
void ObjectPlayer::idle() {
    estado = EstadosPlayer::Inactive;
}

void ObjectPlayer::move_x(Direcciones direccion, int speed) {
    if (direccion == Left) {
        for (int i=0; i <  speed; i++) { //para chequear en cada unidad que se mueve si hay una pared
            //Chequeo si hay una pared al lado (para hacer mas simple miro solo los extremos de y)
            if (position.x -1 <= 0) {
                estado = EstadosPlayer::Inactive;
                return;
            }
            if (GameMundo::casilleros[position.y][x_left].estaBloqueado() || GameMundo::casilleros[pos_y_max][x_left].estaBloqueado()) { 
                //Colison con pared
                std::cout << "pared a la izquierda" << std::endl;
                estado = EstadosPlayer::Inactive;
                return;
            } else { //si no esta bloqueado..
                set_pos_x(position.x -1);
            }
        }
    } else { //Right
        for (int i=0; i < speed; i++) { //para chequear en cada unidad que se mueve si hay una pared
            if (GameMundo::casilleros[position.y][x_right].estaBloqueado() || GameMundo::casilleros[pos_y_max][x_right].estaBloqueado()) { 
                std::cout << "pared a la derecha" << std::endl;
                estado = EstadosPlayer::Inactive;
                return;
            } else { //si no esta bloqueado..
                set_pos_x(position.x + 1);
            }
        }
    }
}

void ObjectPlayer::walk(Direcciones direccion) {
    if (tocandoSuelo) {
        if (intoxicated) {
            estado = EstadosPlayer::IntoxicatedWalk;
            move_x(direccion, INTOXICATED_WALK_SPEED);
        } else {
            estado = EstadosPlayer::Walking;
            move_x(direccion, WALK_SPEED);
        }
    }
}
void ObjectPlayer::run(Direcciones direccion) {
    if (tocandoSuelo) {
        if (intoxicated) {
            estado = EstadosPlayer::IntoxicatedWalk;
            move_x(direccion, INTOXICATED_WALK_SPEED);
        } else {
            estado = EstadosPlayer::Running;
            move_x(direccion, RUN_SPEED);
        }
    }
}

void ObjectPlayer::jump(Direcciones direccion) {
    estado = EstadosPlayer::Jumping;
}

bool ObjectPlayer::shoot(Direcciones direccion) {
    estado = EstadosPlayer::Shooting;
    return false;
}

void ObjectPlayer::fall() {
    for (int i=0; i < FALL_SPEED; i++) {
        //Chequeo si hay una pared debajo (para hacer mas simple miro solo los extremos de x)
        if (GameMundo::casilleros[y_down][position.x].estaBloqueado() || GameMundo::casilleros[y_down][pos_x_max].estaBloqueado()) {
            //Colision con suelo;
            if (estado == EstadosPlayer::Falling)
                estado = EstadosPlayer::Inactive;
            tocandoSuelo = true;
            return;
        } else { 
            //std::cout << "Cayendo" << std::endl;
            tocandoSuelo = false;
            estado = EstadosPlayer::Falling;
            setPosition(Coordenada(position.x, position.y + 1));
        }
    }
}


// setters
void ObjectPlayer::change_weapon(Weapon &&new_weapon) {

}
void ObjectPlayer::pick_up_ammo() {

}

void ObjectPlayer::set_intoxicated_status(bool status) {
    intoxicated = status;
}

void ObjectPlayer::add_points(int points) {
    this->points += points;
}

void ObjectPlayer::take_damage(int &damage) {
    estado = EstadosPlayer::Damaged;
    health -= damage;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}
void ObjectPlayer::revive() {

}

InfoPlayer ObjectPlayer::getInfo() {
    //InfoPlayer info(id, position.x, position.y, tipoPlayer, estado, health, points, weapon.getType(), weapon.getmuniciones());
    InfoPlayer info(id, position.x, position.y, estado, health, points, TipoArma::Blaster, 1); //hardcodeado
    return info;
}
