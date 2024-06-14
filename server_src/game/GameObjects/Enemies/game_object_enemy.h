#ifndef SERVER_ENEMY_H_
#define SERVER_ENEMY_H_

#include <vector>
#include <cstdint>

#include "../game_object.h"
#include "../../../../common_src/info_juego.h"

//fijo
#define WIDTH_BAT 10 //Ajustar luego
#define HEIGHT_BAT 10 //Ajustar luego

class ObjectEnemy : public GameObject {
    private:
    
    protected:
        TipoEnemy tipoEnemy = TipoEnemy::Bat;
        int damage; //daño que realiza
        int health;
        EstadosEnemy enemy_status = EstadosEnemy::Idle;
        std::vector<Coordenada> waypoints;
        int waypoint_actual = 0; // Índice del waypoint actual
        bool alive = true; // Estado de vida del enemigo

    public:
        ObjectEnemy(TipoEnemy tipo, int width, int height,  
                    int damage, int health, 
                    const std::vector<Coordenada>& waypoints);
    
        void move_x();

        void take_damage(int &damage);

        void attack();

        void revive();

        InfoEnemigo getInfo();
};
#endif
