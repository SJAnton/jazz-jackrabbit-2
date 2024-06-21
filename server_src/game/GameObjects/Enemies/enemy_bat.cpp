#include "enemy_bat.h"
#include "../../game_mundo.h"

bool EnemyBat::initialized = false;
int EnemyBat::default_damage = 0;
int EnemyBat::default_health = 0;
int EnemyBat::default_speed = 0;
int EnemyBat::default_points = 0;
int EnemyBat::default_respawn_time = 0;
int EnemyBat::default_ammo_drop_chance = 0;
int EnemyBat::default_movement_range = 0;

void EnemyBat::init(int damage, int health, int speed, int points, int respawn_time,
                    int dropping_ammo_chance, int movement_range) {
    if (!initialized) {
        default_damage = damage;
        default_health = health;
        default_speed = speed;
        default_points = points;
        default_respawn_time = respawn_time;
        default_ammo_drop_chance = dropping_ammo_chance;
        default_movement_range = movement_range;
        initialized = true;
    }
}

void EnemyBat::move_x() {
    // El bat no se detiene si no tiene un piso abajo
    if (direction == Left) {
        for (int i = 0; i < speed; ++i) {
            if (position.x <= 0 || (position.x - 1) > X_MAX || movement_range <= 0 ||
                GameMundo::casilleros[position.y][x_left].estaBloqueado() ||
                GameMundo::casilleros[pos_y_max][x_left].estaBloqueado()) {
                // Bloqueado a la izquierda
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
                GameMundo::casilleros[pos_y_max][x_right].estaBloqueado()) {
                // Bloqueado a la derecha
                status = EstadosEnemy::Idle;
                restore_movement_range();
                break;
            }
            set_pos_x(position.x + 1);
            movement_range--;
        }
    }
}

void EnemyBat::fall() {
    return;
}
