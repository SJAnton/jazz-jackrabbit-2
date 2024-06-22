#include "enemy_diablo.h"

bool EnemyDiablo::initialized = false;
int EnemyDiablo::default_damage = 0;
int EnemyDiablo::default_health = 0;
int EnemyDiablo::default_speed = 0;
int EnemyDiablo::default_points = 0;
int EnemyDiablo::default_respawn_time = 0;
int EnemyDiablo::default_ammo_drop_chance = 0;
int EnemyDiablo::default_movement_range = 0;

void EnemyDiablo::init(int damage, int health, int speed, int points, int respawn_time,
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

EnemyDiablo::EnemyDiablo() : 
    ObjectEnemy(TipoEnemy::Diablo, WIDTH_DIABLO, HEIGHT_DIABLO, default_damage,
                            default_health, default_speed, default_points, default_respawn_time,
                                default_ammo_drop_chance, default_movement_range) {}
