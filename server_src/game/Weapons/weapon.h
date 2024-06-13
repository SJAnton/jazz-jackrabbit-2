#ifndef WEAPON_H
#define WEAPN_H

#include "../../../common_src/constantes.h"

/**
 * Clase de la que heredan todas las diferentes armas
*/
class Weapon
{
private:
    const int maxMuniciones;// cantidad maxima de balas que tiene el arma (varia segun el tipo)
    TipoArma tipoArma;
    int municiones = 1; // cantidad de balas que le quedan
   
public:
    Weapon(int maxMuniciones, TipoArma tipoArma) : maxMuniciones(maxMuniciones), tipoArma(tipoArma) {};

    void addMunicion(int cantMunicion) {
        municiones += cantMunicion;
        if (municiones >= maxMuniciones)
            municiones = maxMuniciones;
    };

    //bool shoot();

    //~Weapon();
};

#endif //WEAPON_H
