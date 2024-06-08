#include "sprites_players.h"
#include "sprites_paths.h"

SpriteSheet SpritesPlayers::Spaz_idle;
SpriteSheet SpritesPlayers::Spaz_walk;
SpriteSheet SpritesPlayers::Spaz_run;
SpriteSheet SpritesPlayers::Spaz_jump;
SpriteSheet SpritesPlayers::Spaz_shoot;
SpriteSheet SpritesPlayers::Spaz_specialAtack;
SpriteSheet SpritesPlayers::Spaz_damaged;
SpriteSheet SpritesPlayers::Spaz_intoxicatedIdle;
SpriteSheet SpritesPlayers::Spaz_intoxicatedWalk;
SpriteSheet SpritesPlayers::Spaz_death;

bool SpritesPlayers::inicializado = false;

void SpritesPlayers::init() {
    if (!inicializado) {
        //Spaz
        Spaz_idle = SpriteSheet(PATH_SPAZ_IDLE, 56, 56, 6);
        Spaz_walk = SpriteSheet(PATH_SPAZ_WALK, 56, 56, 8);
        Spaz_run = SpriteSheet(PATH_SPAZ_JUMP,56, 56, 12);
        Spaz_jump = SpriteSheet(PATH_SPAZ_JUMP, 56, 56, 12);
        Spaz_shoot = SpriteSheet(PATH_SPAZ_SHOOT, 56, 56, 6);
        Spaz_specialAtack = SpriteSheet(PATH_SPAZ_SPECIAL, 56, 56, 12);
        Spaz_damaged = SpriteSheet(PATH_SPAZ_DAMAGED, 56, 56, 11);
        Spaz_intoxicatedIdle = SpriteSheet(PATH_SPAZ_INTOXICATED_IDLE, 56, 56, 8);
        Spaz_intoxicatedWalk = SpriteSheet(PATH_SPAZ_INTOXICATED_WALK,56, 56, 12);
        Spaz_death = SpriteSheet(PATH_SPAZ_DEATH, 96, 96, 26);

        //Lori
        inicializado = true;
    }
}