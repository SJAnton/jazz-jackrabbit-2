#ifndef SPRITES_ENEMIES_H
#define SPRITES_ENEMIES_H

#include "spritesheet.h"

// Esta clase funciona como una libreria. No se deben crear instancias de esta clase
class SpritesEnemies {
public:
    //Bat
    static SpriteSheet Bat_idle;
    static SpriteSheet Bat_attack;
    
    //Rat
    static SpriteSheet Rat_idle;
    static SpriteSheet Rat_walk;
    static SpriteSheet Rat_attack;
    
    //Diablo
    static SpriteSheet Diablo_idle;
    static SpriteSheet Diablo_attack;
    static SpriteSheet Diablo_damaged;

    static void init();
private:
    static bool inicializado;
    SpritesEnemies() {}; // constructor privado para evitar la creacion de instancias
};

#endif
