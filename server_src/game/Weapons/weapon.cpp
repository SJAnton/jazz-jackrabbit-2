#include "weapon.h"

#include <iostream>

// Inicialización de las variables estáticas
bool Weapon::inizializated = false;

int Weapon::diley_shoot_w1 = 0;
int Weapon::diley_shoot_w2 = 0;
int Weapon::diley_shoot_w3 = 0;
int Weapon::diley_shoot_w4 = 0;

void Weapon::init(int delay_shoot_w1, int delay_shoot_w2, int delay_shoot_w3, int delay_shoot_w4) {
    if (!inizializated) {
        diley_shoot_w1 = delay_shoot_w1;
        diley_shoot_w2 = delay_shoot_w2;
        diley_shoot_w3 = delay_shoot_w3;
        diley_shoot_w4 = delay_shoot_w4;
        inizializated = true;
    }
}


Weapon::Weapon(TipoArma tipoArma) : 
    tipoArma(tipoArma) 
{
    if (tipoArma == Tipo_1){
        municiones = -1; // representa infinitas municiones
    }
    else if (tipoArma == Tipo_2){ 
        municiones = 100;  
    }
    else 
        municiones = 0;
}

Weapon::Weapon() : 
    tipoArma(Tipo_1) 
{
    municiones = -1; // representa infinitas municiones
}

void Weapon::addMunicion(int cantMunicion) {
    municiones += cantMunicion;
}

ObjectProjectile Weapon::shoot(const Direcciones &dir, const Coordenada &position) {
    if (municiones > 0 || tipoArma == Tipo_1) {
        municiones--;
        return ObjectProjectile(tipoArma, dir, position);
    } else {
        throw NoAmmoException();
    }
}