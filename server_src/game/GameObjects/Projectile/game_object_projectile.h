#ifndef SERVER_PROJECTILE_H_
#define SERVER_PROJECTILE_H_

#include <memory>
#include <vector>
#include <cstdint>
#include <stdexcept>

#include "../../../../common_src/info_juego.h"
#include "../../../../common_src/constantes_protocolo.h"
#include "../../../../common_src/constantes.h"
#include "../game_object.h"
#include "../game_object.h"

class ObjectPlayer; // Foward declaration para evitar includes cruzados

//Fijo (no lo decide el config)
//#define WIDTH_PROJECTILE 6 //ajustar luego 
//#define HEIGHT_PROJECTILE 4 //ajustar luego

// Simplifico. Sin polimorfismo. Todos los proyectiles hacen lo mismo, 
// lo unico que va a variar segun su tipo es la velocidad y daño que causan
class ObjectProjectile : public GameObject {
    private:
        static bool inizializated;
        //Constantes del config.yaml (cargar con init() una sola vez)
        static int damage_p1;
        static int damage_p2;
        static int damage_p3;
        static int damage_p4;
        static int speed_p1;
        static int speed_p2;
        static int speed_p3;
        static int speed_p4;

    protected:
        TipoArma tipoProyectil;
        Direcciones direction;
        int shooter_id;
        int damage;
        int speed;
        bool exploded = false;

    public:
        static void init(int damage_p1, int damage_p2, int damage_p3, int damage_p4,
                        int speed_p1, int speed_p2, int speed_p3, int speed_p4);
        
        ObjectProjectile(
            TipoArma tipo, const Direcciones &direction,
            const Coordenada &position, int shooter_id
        );

        // Avanza en el eje x en la direccion establecida y velocidad establecida 
        void move_x_pos();

        // Explotar. Retorna el daño que genera el proyectil
        int explode();

        // Devuelve true si el proyectil ya colisionó con algo
        bool is_exploded();

        // Devuelve el ID del player que disparó el proyectil
        int get_shooter_id();

        InfoProyectil getInfo();
};

#endif
