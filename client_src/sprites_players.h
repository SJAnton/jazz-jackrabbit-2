#ifndef SPRITES_PLAYER_H
#define SPRITES_PLAYER_H

#include "spritesheet.h"

// Esta clase funciona como una libreria. No se deben crear instancias de esta clase
class SpritesPlayers {
public:
    static SpriteSheet Spaz_idle;
    static SpriteSheet Spaz_walk;
    static SpriteSheet Spaz_jump;
    static SpriteSheet Spaz_shoot;
    static SpriteSheet Spaz_specialAtack;
    static SpriteSheet Spaz_death;
    static void init();
private:
    static bool inicializado;
    SpritesPlayers() {}; // constructor privado para evitar la creacion de instancias
};

#endif
