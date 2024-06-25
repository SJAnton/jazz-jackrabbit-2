#include "game_object_enemy.h"
#include "../../game_mundo.h"

#include <iostream>

#define EDGE_DISTANCE_LEFT 0
#define EDGE_DISTANCE_RIGHT 30

#define ITR_PER_SEC 15
#define RANDOM_NUMBER_MAX 100

ObjectEnemy::ObjectEnemy(TipoEnemy tipo, int width, int height,  int damage, int health,
                            int speed, int points, int respawn_time, int ammo_drop_chance,
                                int movement_range) :
                                    GameObject(width, height), tipoEnemy(tipo), damage(damage),
                                    health(health), speed(speed), points(points),
                                    respawn_time(respawn_time * ITR_PER_SEC),
                                    ammo_drop_chance(ammo_drop_chance),
                                    movement_range(movement_range)
{
    type = TypeGameObject::Enemy;
    health_buffer = health;
    respawn_time_buffer = respawn_time * ITR_PER_SEC;
    movement_range_buffer = movement_range;
}

void ObjectEnemy::move_x() {
    if (direction == Left) {
        for (int i = 0; i < speed; ++i) {
            if (position.x <= 0 || (position.x - 1) > X_MAX || movement_range <= 0 ||
                GameMundo::casilleros[position.y][x_left].estaBloqueado() ||
                GameMundo::casilleros[pos_y_max][x_left].estaBloqueado()  ||
                !GameMundo::casilleros[y_down][x_left - EDGE_DISTANCE_LEFT].estaBloqueado() ||
                !GameMundo::casilleros[y_down][pos_x_max].estaBloqueado()) {
                // Bloqueado a la izquierda, o no hay piso
                status = EstadosEnemy::Idle;
                restore_movement_range();
                break;
            }
            set_pos_x(position.x - 1);
            movement_range--;
        }
    } else {
        for (int i = 0; i < speed; ++i) {
            if (position.x >= X_MAX || movement_range <= 0 ||
                GameMundo::casilleros[position.y][x_right].estaBloqueado() ||
                GameMundo::casilleros[pos_y_max][x_right].estaBloqueado()  ||
                !GameMundo::casilleros[y_down][x_right + EDGE_DISTANCE_RIGHT].estaBloqueado() ||
                !GameMundo::casilleros[y_down][pos_x_max].estaBloqueado()) {
                // Bloqueado a la derecha, o no hay piso
                status = EstadosEnemy::Idle;
                restore_movement_range();
                break;
            }
            set_pos_x(position.x + 1);
            movement_range--;
        }
    }
}

void ObjectEnemy::walk() {
    if (!is_alive) {
        return;
    }
    status = EstadosEnemy::Attack;
    move_x();
}

void ObjectEnemy::jump() {

}

void ObjectEnemy::fall() {
    if (!is_alive) {
        return;
    }
    for (int i = 0; i < FALL_SPEED; ++i) {
        if (GameMundo::casilleros[y_down][position.x].estaBloqueado() || 
            GameMundo::casilleros[y_down][pos_x_max].estaBloqueado()) {
            status = EstadosEnemy::Attack;
            on_ground = true;
            break;
        }
        on_ground = false;
        status = EstadosEnemy::Idle;
        setPosition(Coordenada(position.x, position.y + 1));
    }
}

TipoEnemy ObjectEnemy::getTipoEnemy() {
    return tipoEnemy;
}

int ObjectEnemy::get_damage() {
    return damage;
}

int ObjectEnemy::get_points() {
    return points;
}

bool ObjectEnemy::is_dead() {
    return !is_alive;
}

bool ObjectEnemy::is_falling() {
    return !on_ground;
}

void ObjectEnemy::update_respawn_time() {
    if (is_alive) {
        return;
    }
    respawn_time--;
    //std::cout << respawn_time << std::endl;
    if (respawn_time <= 0) {
        respawn_time = respawn_time_buffer;
        revive();
    }
}

void ObjectEnemy::restore_movement_range() {
    switch (direction) {
        case Left:
            direction = Right;
            break;
        case Right:
            direction = Left;
            break;
    }
    movement_range = movement_range_buffer * 2; // Recorre de un extremo a otro
}

void ObjectEnemy::take_damage(int &damage) {
    if (!is_alive) {
        return;
    }
    health -= damage;
    if (health <= 0){
        is_alive = false;
        status = EstadosEnemy::Death;
        return;
    } 
    status = EstadosEnemy::Damaged;
}

bool ObjectEnemy::check_ammo_drop() {
    return !is_alive && (std::rand() % RANDOM_NUMBER_MAX < ammo_drop_chance);
}

ObjectCollected ObjectEnemy::drop_ammo() {
    return ObjectCollected(TipoRecolectable::Municion);
}

void ObjectEnemy::attack() {
    status = EstadosEnemy::Attack;
}

void ObjectEnemy::revive() {
    if (is_alive) {
        return;
    }
    is_alive = true;
    health = health_buffer;
    status = EstadosEnemy::Idle;
}

InfoEnemigo ObjectEnemy::getInfo() {
    return InfoEnemigo(tipoEnemy, position.x, position.y, direction, status);
}
