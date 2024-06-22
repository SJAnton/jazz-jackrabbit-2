#ifndef WEAPON_H
#define WEAPN_H

#include "../../../common_src/constantes.h"
#include "../GameObjects/Projectile/game_object_projectile.h"
#include <exception>
#include <string>



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
        static int diley_shoot_w1;
        static int diley_shoot_w2;
        static int diley_shoot_w3;
        static int diley_shoot_w4;
        
private:
    TipoArma tipoArma;
    int municiones = 0; // cantidad de balas que le quedan
   
public:
    static void init(int diley_shoot_w1, int diley_shoot_w2, int diley_shoot_w3, int diley_shoot_w4);

    Weapon(); //Constructor por defecto

    Weapon(TipoArma tipoArma);

    void addMunicion(int cantMunicion);

    TipoArma getType() {return tipoArma;};

    int getMuniciones() {return municiones;};

    // devuelve un proyectil si se pudo disparar
    ObjectProjectile shoot(const Direcciones &dir, const Coordenada &position);

};

#endif //WEAPON_H
