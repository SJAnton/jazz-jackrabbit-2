#ifndef SPRITES_PLAYER_H
#define SPRITES_PLAYER_H

#include "spritesheet.h"

// Esta clase funciona como una libreria. No se deben crear instancias de esta clase
class SpritesPlayers {
public:
    //Jazz
    static SpriteSheet Jazz_idle;
    static SpriteSheet Jazz_walk;
    static SpriteSheet Jazz_run;
    static SpriteSheet Jazz_jump;
    static SpriteSheet Jazz_fall;
    static SpriteSheet Jazz_shoot;
    static SpriteSheet Jazz_specialAtack;
    static SpriteSheet Jazz_damaged;
    static SpriteSheet Jazz_intoxicatedIdle;
    static SpriteSheet Jazz_intoxicatedWalk;
    static SpriteSheet Jazz_dying;
    static SpriteSheet Jazz_death;
    //Spaz
    static SpriteSheet Spaz_idle;
    static SpriteSheet Spaz_walk;
    static SpriteSheet Spaz_run;
    static SpriteSheet Spaz_jump;
    static SpriteSheet Spaz_fall;
    static SpriteSheet Spaz_shoot;
    static SpriteSheet Spaz_specialAtack;
    static SpriteSheet Spaz_damaged;
    static SpriteSheet Spaz_intoxicatedIdle;
    static SpriteSheet Spaz_intoxicatedWalk;
    static SpriteSheet Spaz_dying;
    static SpriteSheet Spaz_death;
    //Lori
    static SpriteSheet Lori_idle;
    static SpriteSheet Lori_walk;
    static SpriteSheet Lori_run;
    static SpriteSheet Lori_jump;
    static SpriteSheet Lori_fall;
    static SpriteSheet Lori_shoot;
    static SpriteSheet Lori_specialAtack;
    static SpriteSheet Lori_damaged;
    static SpriteSheet Lori_intoxicatedIdle;
    static SpriteSheet Lori_intoxicatedWalk;
    static SpriteSheet Lori_dying;
    static SpriteSheet Lori_death;
    static void init();
private:
    static bool inicializado;
    SpritesPlayers() {}; // constructor privado para evitar la creacion de instancias
};

#endif
