#include "enemy_rat.h"

bool EnemyRat::initialized = false;
int EnemyRat::Default_Damage = 0;
int EnemyRat::Default_Health = 0;

void EnemyRat::init(int damage, int health) {
    if (!initialized) {
        Default_Damage = damage;
        Default_Health = health;
        initialized = true;
    }
}

// Implementación de otros miembros de la clase
