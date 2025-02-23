#include <iostream>
#include <utility> 

#include "../../game_mundo.h"
#include "game_object_player.h"

// Inicializo las variables estáticas
bool ObjectPlayer::inicializado = false;
int ObjectPlayer::defaultHealth = 0;
int ObjectPlayer::defaultDamageAttack = 0;
int ObjectPlayer::defaultWalkSpeed = 0;
int ObjectPlayer::defaultRunSpeed = 0;
int ObjectPlayer::defaultIntoxicatedSpeed = 0;
int ObjectPlayer::defaultJumpSpeed = 0;
int ObjectPlayer::defaultFallSpeed = 0;

void ObjectPlayer::init(int health, int damageAttack, int speed_walk, int speed_run, int speed_intoxicated, int speed_jump, int speed_fall) {
    if (!inicializado) {
        defaultHealth = health;
        defaultDamageAttack = damageAttack;
        defaultWalkSpeed = speed_walk;
        defaultRunSpeed = speed_run;
        defaultIntoxicatedSpeed = speed_intoxicated;
        defaultJumpSpeed = speed_jump;
        defaultFallSpeed = speed_fall;
        inicializado = true;
    }
}


ObjectPlayer::ObjectPlayer(int id, const TipoPlayer &tipo) :
    GameObject(WIDTH_PLAYER, HEIGHT_PLAYER),
    id(id), 
    tipoPlayer(tipo),
    health(defaultHealth),
    health_buffer(health)
    //weapon(Tipo_1)   
{
    std::cout << health_buffer << std::endl;

    type = TypeGameObject::Player;
    initialize_weapons();
    weapon = &weapons[weaponIndex];
}


// Movimientos

void ObjectPlayer::idle() {
 if (!alive || isDoingSpecialAttack)
        return;
    estado = EstadosPlayer::Inactive;
    if (intoxicated)
        estado = EstadosPlayer::IntoxicatedIdle;
}

bool ObjectPlayer::move_x(Direcciones direccion, int speed) {
    direction = direccion;
    if (direccion == Left) {
        for (int i=0; i <  speed; i++) { //para chequear en cada unidad que se mueve si hay una pared
            if (position.x  <= 0 || position.x -1 > X_MAX) {
                //estado = EstadosPlayer::Inactive;
                return false;
            }
            //Chequeo si hay una pared al lado (para hacer mas simple miro solo los extremos de y)
            if (GameMundo::casilleros[position.y][x_left].estaBloqueado() || GameMundo::casilleros[pos_y_max][x_left].estaBloqueado()) { 
                //Colison con pared a la izquierda
                //estado = EstadosPlayer::Inactive;
                return false;
            } else { //si no esta bloqueado..
                set_pos_x(position.x -1);
            }
        }
    } else { //Right
        for (int i=0; i < speed; i++) { //para chequear en cada unidad que se mueve si hay una pared
            if (GameMundo::casilleros[position.y][x_right].estaBloqueado() || GameMundo::casilleros[pos_y_max][x_right].estaBloqueado()) { 
                //std::cout << "pared a la derecha" << std::endl;
                //estado = EstadosPlayer::Inactive;
                return false;
            } else { //si no esta bloqueado..
                set_pos_x(position.x + 1);
            }
        }
    }
    return true;
}

bool ObjectPlayer::move_y(int speed) {
    for (int i=0; i <  speed; i++) { //para chequear en cada unidad que se mueve si hay una pared
        if (position.y  <= 0 || position.y >= Y_MAX) { // si me salgo del mapa...
            estado = EstadosPlayer::Falling;
            is_jumping = false;
            falling = true;
            timer_jump = 0; //reseteo el timer a 0
            std::cout << "me fui de rango. pos y " << position.y << std::endl;
            return false;
        }
        //Chequeo si hay una pared arriba 
        if (GameMundo::casilleros[y_up][position.x].estaBloqueado() || 
            GameMundo::casilleros[y_up][pos_x_max].estaBloqueado()) { 
            //Colison con pared arriba
            is_jumping = false;
            falling = true;
            timer_jump = 0; //reseteo el timer a 0
            estado = EstadosPlayer::Falling;
            return false;
        } else { //si no
            set_pos_y(position.y - 1); // se mueve 1 casillero hacia arriba
            //if (i % 3 == 0)
              //  move_x(direction, defaultJumpSpeed/4);
        }
    }
    return true;
}
bool ObjectPlayer::down_y(int speed) {
    for (int i=0; i < speed; i++) {
        //Chequeo si hay una pared debajo (para hacer mas simple miro solo los extremos de x)
        if (GameMundo::casilleros[y_down][position.x].estaBloqueado() || 
            GameMundo::casilleros[y_down][pos_x_max].estaBloqueado()) {
            //Colision con suelo;
            //estado = EstadosPlayer::Inactive;
            tocandoSuelo = true;
            falling = false;
            //is_jumping = false;
            return false;
        } else { 
            //std::cout << "Cayendo" << std::endl;
            tocandoSuelo = false;
            falling = true;
            setPosition(Coordenada(position.x, position.y + 1));
        }
    }
    return true;
}
void ObjectPlayer::walk(Direcciones direccion) {
    if (!alive || isDoingSpecialAttack || estado == EstadosPlayer::Shooting)
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
    if (!alive || isDoingSpecialAttack)
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
    if (!tocandoSuelo || !alive || is_jumping || isDoingSpecialAttack) { //si estoy en el aire, haciendo el ataque especial o muerto no puedo saltar
        return;
    }
    estado = EstadosPlayer::Jumping;
    is_jumping = true;
    tocandoSuelo = false;
    direction = direccion;
    updateJump();
}

void ObjectPlayer::updateShootingDelay() {
    if (weapon->canShoot()) {
        return;
    }
    weapon->updateDelay();
}

void ObjectPlayer::updateDamageWaitTime() {
    damage_wait_time--;
    if (damage_wait_time <= 0) {
        damage_wait_time = damage_wait_buffer;
        can_take_damage = true;
    }
}

ObjectProjectile ObjectPlayer::shoot(Direcciones dir) {
    if (estado == EstadosPlayer::Inactive) {
        estado = EstadosPlayer::Shooting;
    }
    Coordenada pos(x_left - 8, pos_y_max - height/2);
    if (dir == Right)
        pos = Coordenada(pos_x_max+4, pos_y_max - height/2);

    return weapon->shoot(direction, pos, id);
}

void ObjectPlayer::fall() {
    if (is_jumping || isDoingSpecialAttack) { //si estoy saltando no debo caer
        return;
    }
    for (int i=0; i < ObjectPlayer::defaultFallSpeed; ++i) {
        //Chequeo si hay una pared debajo (para hacer mas simple miro solo los extremos de x)
        if (GameMundo::casilleros[y_down][position.x].estaBloqueado() || 
            GameMundo::casilleros[y_down][pos_x_max].estaBloqueado()) {
            //Colision con suelo;
            if (estado == EstadosPlayer::Falling)
                estado = EstadosPlayer::Inactive;
            tocandoSuelo = true;
            falling = false;
            //is_jumping = false;
            return;
        } else { 
            //std::cout << "Cayendo" << std::endl;
            tocandoSuelo = false;
            falling = true;
            estado = EstadosPlayer::Falling;
            setPosition(Coordenada(position.x, position.y + 1));
        }
    }
}

void ObjectPlayer::rebounceFromEnemy() {
    if (!alive) {
        return;
    } else if (is_jumping || falling) {
        // Eje Y
        rebounceFall();
    } else {
        rebounceSides();
        rebouncing_sides = true;
    }
}

void ObjectPlayer::rebounceFall() {
    Direcciones prev_dir = direction;
    for (int i = 0; i < ObjectPlayer::defaultFallSpeed; ++i) {
        tocandoSuelo = false;
        falling = true;
        estado = EstadosPlayer::Damaged;
        if (prev_dir == Right) {
            setPosition(Coordenada(position.x - 1, position.y + 1));
        } else {
            setPosition(Coordenada(position.x + 1, position.y + 1));
        }
        direction = prev_dir;
    }
}

void ObjectPlayer::rebounceSides() {
    for (int i = 0; i < ObjectPlayer::defaultWalkSpeed; ++i) {
        estado = EstadosPlayer::Damaged;
        if (direction == Right) {
            setPosition(Coordenada(position.x - 1, position.y - 1));
        } else {
            setPosition(Coordenada(position.x + 1, position.y - 1));
        }
    }
}

EstadosPlayer ObjectPlayer::getEstado() {
    return estado;
}

// setters

void ObjectPlayer::change_weapon() {
    weaponIndex++;
    if (weaponIndex >= (int)weapons.size()) {
        weaponIndex = 0;
    }
    weapon = &weapons[weaponIndex];
}

void ObjectPlayer::pick_up_ammo(int ammo, int weapon_index) {
    weapons[weapon_index].addMunicion(ammo);
}

void ObjectPlayer::initialize_weapons() {
    weapons.push_back(Weapon(Tipo_1));
    weapons.push_back(Weapon(Tipo_2));
    weapons.push_back(Weapon(Tipo_3));
    weapons.push_back(Weapon(Tipo_4));
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
    can_take_damage = false;
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
    health = health_buffer;
    alive = true;
    estado = EstadosPlayer::Reviving;
}

InfoPlayer ObjectPlayer::getInfo() {
    return InfoPlayer(id, position.x, position.y, direction, tipoPlayer, estado, health, points, weapon->getType(), weapon->getMuniciones());
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

int ObjectPlayer::getSpecialAttackDamage() {
    switch (tipoPlayer) {
    case Jazz:
        return 100;
    case Lori: 
        return 100;
    case Spaz: 
        return 100;
    default: 
        return 0;
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
    } else {
        move_y(defaultJumpSpeed);
    }
}

void ObjectPlayer::updateRebounceSides() {
    timer_rebounce_sides++;
    if (timer_rebounce_sides >= TIME_REBOUNCE_SIDES) {
        rebouncing_sides = false;
        timer_rebounce_sides = 0;
    } else {
        rebounceSides();
    }
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



