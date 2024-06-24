#ifndef SERVER_ENEMY_H_
#define SERVER_ENEMY_H_

#include <vector>
#include <cstdint>
#include <cstdlib>

#include "../game_object.h"
#include "../Collected/game_object_collected.h"
#include "../../../../common_src/info_juego.h"

//#define WIDTH_BAT 80
//#define HEIGHT_BAT 40
//#define WIDTH_DIABLO 20                                 // padding left 20px
//#define HEIGHT_DIABLO 40                                // pading up 15px
//#define WIDTH_RAT 80
//#define HEIGHT_RAT 40

#define FALL_SPEED 10

class ObjectEnemy : public GameObject {
    private:
    
    protected:
        TipoEnemy tipoEnemy = TipoEnemy::Bat;

        int damage;
        int health;
        int speed;
        int points;
        int respawn_time;

        int ammo_drop_chance;

        int movement_range;

        EstadosEnemy status = EstadosEnemy::Idle;

        bool is_alive = true;

        bool on_ground = true;

        Direcciones direction = (std::rand() % 2 == 0) ? Left : Right;

        int health_buffer;

        int respawn_time_buffer;

        int movement_range_buffer;

        virtual void move_x();

        void restore_movement_range();

    public:
        ObjectEnemy(TipoEnemy tipo, int width, int height, int damage,
                        int health, int speed, int points, int respawn_time,
                            int ammo_drop_chance, int movement_range);

        virtual void walk();
        void jump();
        virtual void fall();

        TipoEnemy getTipoEnemy();

        int get_damage();

        int get_points();

        bool is_dead();

        bool is_falling();

        void update_respawn_time();

        void take_damage(int &damage);

        bool check_ammo_drop();

        ObjectCollected drop_ammo();

        void attack();

        void revive();

        InfoEnemigo getInfo();
};
#endif
