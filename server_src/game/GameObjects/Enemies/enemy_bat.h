#ifndef OBJECT_ENEMY_BAT
#define OBJECT_ENEMY_BAT

#include "game_object_enemy.h"

class EnemyBat : public ObjectEnemy {
    private:
        static bool initialized;

        static int default_damage;

        static int default_health;

        static int default_speed;

        static int default_points;

        static int default_respawn_time;

        static int default_ammo_drop_chance;

        static int default_movement_range;

    public:
        EnemyBat() : ObjectEnemy(TipoEnemy::Bat, WIDTH_BAT, HEIGHT_BAT, default_damage,
                        default_health, default_speed, default_points, default_respawn_time,
                            default_ammo_drop_chance, default_movement_range) {}

        static void init(int damage, int health, int speed, int points,
                            int respawn_time, int ammo_drop_chance, int movement_range);
        
        void move_x() override;

        void fall() override;
};
#endif
