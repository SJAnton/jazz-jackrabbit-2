#include "enemy_rat.h"

bool EnemyRat::initialized = false;
int EnemyRat::default_damage = 0;
int EnemyRat::default_health = 0;
int EnemyRat::default_speed = 0;
int EnemyRat::default_points = 0;
int EnemyRat::default_respawn_time = 0;
int EnemyRat::default_ammo_drop_chance = 0;
int EnemyRat::default_movement_range = 0;

void EnemyRat::init(int damage, int health, int speed, int points, int respawn_time,
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

EnemyRat::EnemyRat(
    TipoEnemy tipo, int width, int height, int damage, int health, int speed,
    int points, int respawn_time, int ammo_drop_chance, int movement_range
) : ObjectEnemy(tipo, width, height, damage, health, speed, points, respawn_time,
                ammo_drop_chance, movement_range) {};
