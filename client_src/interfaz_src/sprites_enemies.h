#ifndef SPRITES_ENEMIES_H
#define SPRITES_ENEMIES_H

#include "spritesheet.h"

// Esta clase funciona como una libreria. No se deben crear instancias de esta clase
class SpritesPlayers {
public:
    //Bat
    static SpriteSheet Bat_idle;
    static SpriteSheet Bat_Attack;
    
    //Rat
    static SpriteSheet Rat_idle;
    static SpriteSheet Rat_walk;
    static SpriteSheet Rat_attack;
    
    //Diablo
    static SpriteSheet Diablo_idle;
    static SpriteSheet Diablo_attack;
    static SpriteSheet Diablo_appear;
    static SpriteSheet Diablo_disappear;

    static void init();
private:
    static bool inicializado;
    SpritesPlayers() {}; // constructor privado para evitar la creacion de instancias
};

#endif
