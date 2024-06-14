#include "game_object_player.h"
#include <iostream>


#include "../../game_mundo.h"

// Inicializo las variables estáticas
bool ObjectPlayer::inicializado = false;
int ObjectPlayer::defaultHealth = 0;
int ObjectPlayer::defaultWalkSpeed = 0;
int ObjectPlayer::defaultRunSpeed = 0;
int ObjectPlayer::defaultIntoxicatedSpeed = 0;
int ObjectPlayer::defaultJumpSpeed = 0;
int ObjectPlayer::defaultFallSpeed = 0;


void ObjectPlayer::init(int health, int speed_walk, int speed_run, int speed_intoxicated, int speed_jump, int speed_fall) {
    if (!inicializado) {
        defaultHealth = health;
        defaultWalkSpeed = speed_walk;
        defaultRunSpeed = speed_run;
        defaultIntoxicatedSpeed = speed_intoxicated;
        defaultFallSpeed = speed_fall;
        inicializado = true;
    }
}

ObjectPlayer::ObjectPlayer(int id, TipoPlayer &tipo, const Weapon &weapon) :
    GameObject(WIDTH_PLAYER, HEIGHT_PLAYER),
    id(id), 
    tipoPlayer(tipo),
    health(defaultHealth),
    weapon(weapon)   
{
    type = TypeGameObject::Player;
}


// Movimientos

void ObjectPlayer::idle() {
    estado = EstadosPlayer::Inactive;
    if (intoxicated)
        estado = EstadosPlayer::IntoxicatedIdle;
}

void ObjectPlayer::move_x(Direcciones direccion, int speed) {
    if (direccion == Left) {
        for (int i=0; i <  speed; i++) { //para chequear en cada unidad que se mueve si hay una pared
            //Chequeo si hay una pared al lado (para hacer mas simple miro solo los extremos de y)
            if (position.x  <= 0 || position.x -1 > X_MAX) {
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
            move_x(direccion, ObjectPlayer::defaultIntoxicatedSpeed);
        } else {
            estado = EstadosPlayer::Walking;
            move_x(direccion, ObjectPlayer::defaultWalkSpeed);
        }
    }
}

void ObjectPlayer::run(Direcciones direccion) {
    if (tocandoSuelo) {
        if (intoxicated) {
            estado = EstadosPlayer::IntoxicatedWalk;
            move_x(direccion, ObjectPlayer::defaultIntoxicatedSpeed);
        } else {
            estado = EstadosPlayer::Running;
            move_x(direccion, ObjectPlayer::defaultRunSpeed);
        }
    }
}

void ObjectPlayer::jump(Direcciones direccion) {
    estado = EstadosPlayer::Jumping;
}

ObjectProjectile ObjectPlayer::shoot(Direcciones dir) {
    estado = EstadosPlayer::Shooting;
    Coordenada pos(pos_x_max+4, pos_y_max - height/2); // ajustar visualmente
    return ObjectProjectile(TipoProyectil::Tipo_1, dir, pos);
    //return ObjectProjectile(weapon.getTipo(), dir, pos);
}

void ObjectPlayer::fall() {
    for (int i=0; i < ObjectPlayer::defaultFallSpeed; i++) {
        //Chequeo si hay una pared debajo (para hacer mas simple miro solo los extremos de x)
        if (GameMundo::casilleros[y_down][position.x].estaBloqueado() || 
            GameMundo::casilleros[y_down][pos_x_max].estaBloqueado()) {
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
void ObjectPlayer::pick_up_ammo(int ammo) {
    std::cout << "arma suma municiones" << std::endl;
    //weapon.addMunicion(ammo);
}

void ObjectPlayer::set_intoxicated_status(bool status) {
    intoxicated = status;
}

void ObjectPlayer::add_points(int points) {
    this->points += points;
}

void ObjectPlayer::add_hearts(int pts_vidas) {
    if (pts_vidas < 0) {
        intoxicated = true;
    }
    health += pts_vidas;
    if (health > defaultHealth)
        health = defaultHealth;
    else if (health <= 0)
        alive = false;
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
    InfoPlayer info(id, position.x, position.y, tipoPlayer, estado, health, points,  TipoArma::Blaster, 1); //hardcodeado
    return info;
}
