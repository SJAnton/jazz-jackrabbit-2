#include "enemy_bat.h"

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

void EnemyBat::fall() {
    return;
}
