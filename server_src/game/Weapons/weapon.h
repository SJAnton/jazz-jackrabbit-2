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

    void subMunicion() {
        municiones--;
        if (municiones <= 0)
            municiones = 0;
     };


    void setType(const TipoArma &type) {tipoArma = type;};

    TipoArma getType() {return tipoArma;};

    int getMuniciones() {return municiones;};

    //~Weapon();
};

#endif //WEAPON_H
