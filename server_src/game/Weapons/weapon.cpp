#include "weapon.h"

#include <iostream>

// Inicialización de las variables estáticas
bool Weapon::inizializated = false;

int Weapon::delay_shoot_w1 = 0;
int Weapon::delay_shoot_w2 = 0;
int Weapon::delay_shoot_w3 = 0;
int Weapon::delay_shoot_w4 = 0;

int Weapon::buffer_shoot_w1 = 0;
int Weapon::buffer_shoot_w2 = 0;
int Weapon::buffer_shoot_w3 = 0;
int Weapon::buffer_shoot_w4 = 0;

void Weapon::init(int delay_w1, int delay_w2, int delay_w3, int delay_w4) {
    if (!inizializated) {
        delay_shoot_w1 = delay_w1;
        delay_shoot_w2 = delay_w2;
        delay_shoot_w3 = delay_w3;
        delay_shoot_w4 = delay_w4;

        buffer_shoot_w1 = delay_w1;
        buffer_shoot_w2 = delay_w2;
        buffer_shoot_w3 = delay_w3;
        buffer_shoot_w4 = delay_w4;

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

void Weapon::updateDelay() {
    switch (tipoArma) {
        case TipoArma::Tipo_1:
            delay_shoot_w1--;
            if (delay_shoot_w1 <= 0) {
                can_shoot = true;
                delay_shoot_w1 = buffer_shoot_w1;
            }
            break;
        case TipoArma::Tipo_2:
            delay_shoot_w2--;
            if (delay_shoot_w2 <= 0) {
                can_shoot = true;
                delay_shoot_w2 = buffer_shoot_w2;
            }
            break;
        case TipoArma::Tipo_3:
            delay_shoot_w3--;
            if (delay_shoot_w3 <= 0) {
                can_shoot = true;
                delay_shoot_w3 = buffer_shoot_w3;
            }
            break;
        case TipoArma::Tipo_4:
            delay_shoot_w4--;
            if (delay_shoot_w4 <= 0) {
                can_shoot = true;
                delay_shoot_w4 = buffer_shoot_w4;
            }
            break;
        default:
            throw std::runtime_error("Weapon delay not found");
    }
}

ObjectProjectile Weapon::shoot(const Direcciones &dir, const Coordenada &position, int shooter_id) {
    if (municiones > 0 || tipoArma == Tipo_1) {
        municiones--;
        can_shoot = false;
        return ObjectProjectile(tipoArma, dir, position, shooter_id);
    } else {
        throw NoAmmoException();
    }
}