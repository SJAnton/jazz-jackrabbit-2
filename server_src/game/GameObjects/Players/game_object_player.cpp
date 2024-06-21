#include <iostream>

#include "../../game_mundo.h"
#include "game_object_player.h"

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
        defaultJumpSpeed = speed_jump;
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
    direction = direccion;
    if (direccion == Left) {
        for (int i=0; i <  speed; i++) { //para chequear en cada unidad que se mueve si hay una pared
            if (position.x  <= 0 || position.x -1 > X_MAX) {
                //estado = EstadosPlayer::Inactive;
                return;
            }
            //Chequeo si hay una pared al lado (para hacer mas simple miro solo los extremos de y)
            if (GameMundo::casilleros[position.y][x_left].estaBloqueado() || GameMundo::casilleros[pos_y_max][x_left].estaBloqueado()) { 
                //Colison con pared
                //std::cout << "pared a la izquierda" << std::endl;
                //estado = EstadosPlayer::Inactive;
                return;
            } else { //si no esta bloqueado..
                set_pos_x(position.x -1);
            }
        }
    } else { //Right
        for (int i=0; i < speed; i++) { //para chequear en cada unidad que se mueve si hay una pared
            if (GameMundo::casilleros[position.y][x_right].estaBloqueado() || GameMundo::casilleros[pos_y_max][x_right].estaBloqueado()) { 
                //std::cout << "pared a la derecha" << std::endl;
                //estado = EstadosPlayer::Inactive;
                return;
            } else { //si no esta bloqueado..
                set_pos_x(position.x + 1);
            }
        }
    }
}

void ObjectPlayer::move_xy() {
    for (int i=0; i <  defaultJumpSpeed; i++) { //para chequear en cada unidad que se mueve si hay una pared
        if (position.y  <= 0 || position.y >= Y_MAX) { // si me salgo del mapa...
            estado = EstadosPlayer::Falling;
            is_jumping = false;
            falling = true;
            timer_jump = 0; //reseteo el timer a 0
            std::cout << "me fui de rango. pos y " << position.y << std::endl;
            return;
        }
        //Chequeo si hay una pared arriba 
        if (GameMundo::casilleros[y_up][position.x].estaBloqueado() || 
            GameMundo::casilleros[y_up][pos_x_max].estaBloqueado()) { 
            //Colison con pared arriba
            //std::cout << "pared a arriba" << std::endl;
            is_jumping = false;
            falling = true;
            timer_jump = 0; //reseteo el timer a 0
            estado = EstadosPlayer::Falling;
            return;
        } else { //si no
            set_pos_y(position.y - 1); // se mueve 1 casillero hacia arriba
            if (i % 3 == 0)
                move_x(direction, defaultJumpSpeed/4);
        }
    }
}

void ObjectPlayer::walk(Direcciones direccion) {
    if (!alive)
        return;

    direction = direccion;

    if (tocandoSuelo) {
        if (intoxicated) {
            estado = EstadosPlayer::IntoxicatedWalk;
            move_x(direccion, ObjectPlayer::defaultIntoxicatedSpeed);
        } else {
            estado = EstadosPlayer::Walking;
            move_x(direccion, ObjectPlayer::defaultWalkSpeed);
        }
    } else { //estoy en el aire
        move_x(direccion, ObjectPlayer::defaultWalkSpeed); // me muevo sin cambiar el estado
    }
}

void ObjectPlayer::run(Direcciones direccion) {
    if (!alive)
        return;

    if (tocandoSuelo) {
        if (intoxicated) {
            estado = EstadosPlayer::IntoxicatedWalk;
            move_x(direccion, ObjectPlayer::defaultIntoxicatedSpeed);
        } else {
            estado = EstadosPlayer::Running;
            move_x(direccion, ObjectPlayer::defaultRunSpeed);
        }
    }
    else { //estoy en el aire
        move_x(direccion, ObjectPlayer::defaultWalkSpeed); // me muevo sin cambiar el estado
    }
}

void ObjectPlayer::jump(Direcciones direccion) {
    if (!tocandoSuelo || !alive || is_jumping) { //si estoy cayendo, saltando o muerto no puedo saltar
        return;
    }
    estado = EstadosPlayer::Jumping;
    is_jumping = true;
    tocandoSuelo = false;
    direction = direccion;
    updateJump();
}

ObjectProjectile ObjectPlayer::shoot(Direcciones dir) {
    if (estado == EstadosPlayer::Inactive) {
        estado = EstadosPlayer::Shooting;
    }
    Coordenada pos(x_left - 8, pos_y_max - height/2);
    if (dir == Right)
        pos = Coordenada(pos_x_max+4, pos_y_max - height/2);
    
    return weapon.shoot(direction, pos);
    /*
        if (dir == Left) {
            Coordenada pos(x_left - 8, pos_y_max - height/2); // ajustar visualmente
            return ObjectProjectile(weapon.getType(), dir, pos);
        }
        Coordenada pos(pos_x_max+4, pos_y_max - height/2); // ajustar visualmente
        return ObjectProjectile(weapon.getType(), dir, pos);
    */
}

void ObjectPlayer::fall() {
    if (is_jumping) { //si estoy saltando no debo caer
        return;
    }
    for (int i=0; i < ObjectPlayer::defaultFallSpeed; i++) {
        //Chequeo si hay una pared debajo (para hacer mas simple miro solo los extremos de x)
        if (GameMundo::casilleros[y_down][position.x].estaBloqueado() || 
            GameMundo::casilleros[y_down][pos_x_max].estaBloqueado()) {
            //Colision con suelo;
            if (estado == EstadosPlayer::Falling)
                estado = EstadosPlayer::Inactive;
            tocandoSuelo = true;
            //falling = false;
            //is_jumping = false;
            return;
        } else { 
            //std::cout << "Cayendo" << std::endl;
            tocandoSuelo = false;
            //falling = true;
            estado = EstadosPlayer::Falling;
            setPosition(Coordenada(position.x, position.y + 1));
        }
    }
}


EstadosPlayer ObjectPlayer::getEstado() {
    return estado;
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

void ObjectPlayer::set_jumping_status(const bool &status) {
    is_jumping = status;
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
        death();
    }
}

void ObjectPlayer::death() {
    health = 0;
    alive = false;
    is_dying = true;
    estado = EstadosPlayer::Dying;
}
void ObjectPlayer::revive() {
    health = 10;
    alive = true;
    estado = EstadosPlayer::Inactive;
}

InfoPlayer ObjectPlayer::getInfo() {
    return InfoPlayer(id, position.x, position.y, direction, tipoPlayer, estado, health, points, weapon.getType(), weapon.getMuniciones());
}

int ObjectPlayer::getTimeDying() {
    switch (tipoPlayer)
    {
    case Jazz: return TIME_DYING_JAZZ;
    case Lori: return TIME_DYING_LORI;
    case Spaz: return TIME_DYING_SPAZ;
    default: 
        return TIME_DYING_LORI;
    }
}

void ObjectPlayer::updateShoot() {
    timer_shoot++;
    if (timer_shoot >= TIME_SHOOT) {
        estado = EstadosPlayer::Inactive;
    }
}

void ObjectPlayer::updateJump() {
    timer_jump++;
    if (timer_jump >= TIME_JUMP) {
        estado = EstadosPlayer::Falling;
        is_jumping = false;
        falling = true;
        timer_jump = 0;
    } 
    else {
        move_xy();
        }
    
    /*else { // caida en parabola
        //move_x(direction, defaultFallSpeed);
        timer_jump--;
        if (timer_jump <= 0 || falling == false) { //si toca el suelo, el metodo fall() cambiará el valor de falling
            is_jumping = false;
            std::cout << "termino el salto" << std::endl;
        }

    }
    */

}



void ObjectPlayer::updateDeath() {
    if (alive)
        return;
    timer_dying++;
    if (timer_dying >= getTimeDying()) {
        estado = EstadosPlayer::Dead;
        timer_death++;
        if (timer_death >= TIME_DEATH) {
            timer_dying = 0;
            timer_death = 0;
            revive();
        }
    }
}



