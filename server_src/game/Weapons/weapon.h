#ifndef WEAPON_H
#define WEAPON_H

#include <memory>
#include <string>
#include <exception>

#include "../../../common_src/constantes.h"
//#include "../GameObjects/Players/game_object_player.h"
#include "../GameObjects/Projectile/game_object_projectile.h"

class ObjectPlayer; // Foward declaration para evitar includes cruzados

// Excepcion que me dice que no hay municiones
class NoAmmoException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "No hay municiones disponibles";
    }
};


/**
 * Todas las armas van a hacer lo mismo. Lo unico en que varian según su tipo son la 
 * velocidad de disparo (tiempo entre un disparo y otro)
 * 
 * (la  velocidad  y el daño del proyectil estan en la clase ObjectProyectile)
 * 
*/
class Weapon
{
protected:
        static bool inizializated;

        //Constantes del config.yaml (cargar con init() una sola vez)
        static int delay_shoot_w1;
        static int delay_shoot_w2;
        static int delay_shoot_w3;
        static int delay_shoot_w4;

        // Para reestablecer el valor de delay_shoot
        static int buffer_shoot_w1;
        static int buffer_shoot_w2;
        static int buffer_shoot_w3;
        static int buffer_shoot_w4;
        
private:
    TipoArma tipoArma;
    int municiones = 0; // cantidad de balas que le quedan
   
    bool can_shoot = true;

public:
    static void init(int diley_shoot_w1, int diley_shoot_w2, int diley_shoot_w3, int diley_shoot_w4);

    Weapon(); //Constructor por defecto

    Weapon(TipoArma tipoArma);

    void addMunicion(int cantMunicion);

    void updateDelay();

    bool canShoot() {return can_shoot;};

    TipoArma getType() {return tipoArma;};

    int getMuniciones() {return municiones;};

    // devuelve un proyectil si se pudo disparar
    ObjectProjectile shoot(const Direcciones &dir, const Coordenada &position, int shooter_id);

};

#endif //WEAPON_H
