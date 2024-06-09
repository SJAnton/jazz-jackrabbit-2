#include "sprites_players.h"
#include "sprites_paths.h"

//Tengo que declararlos aca porque son static

SpriteSheet SpritesPlayers::Spaz_idle;
SpriteSheet SpritesPlayers::Spaz_walk;
SpriteSheet SpritesPlayers::Spaz_run;
SpriteSheet SpritesPlayers::Spaz_jump;
SpriteSheet SpritesPlayers::Spaz_fall;
SpriteSheet SpritesPlayers::Spaz_shoot;
SpriteSheet SpritesPlayers::Spaz_specialAtack;
SpriteSheet SpritesPlayers::Spaz_damaged;
SpriteSheet SpritesPlayers::Spaz_intoxicatedIdle;
SpriteSheet SpritesPlayers::Spaz_intoxicatedWalk;
SpriteSheet SpritesPlayers::Spaz_death;

//Lori
SpriteSheet SpritesPlayers::Lori_idle;
SpriteSheet SpritesPlayers::Lori_walk;
SpriteSheet SpritesPlayers::Lori_run;
SpriteSheet SpritesPlayers::Lori_jump;
SpriteSheet SpritesPlayers::Lori_fall;
SpriteSheet SpritesPlayers::Lori_shoot;
SpriteSheet SpritesPlayers::Lori_specialAtack;
SpriteSheet SpritesPlayers::Lori_damaged;
SpriteSheet SpritesPlayers::Lori_intoxicatedIdle;
SpriteSheet SpritesPlayers::Lori_intoxicatedWalk;
SpriteSheet SpritesPlayers::Lori_dying;
SpriteSheet SpritesPlayers::Lori_death;

bool SpritesPlayers::inicializado = false;

void SpritesPlayers::init() {
    if (!inicializado) {
        //Spaz
        Spaz_idle = SpriteSheet(PATH_SPAZ_IDLE, 56, 56, 6);
        Spaz_walk = SpriteSheet(PATH_SPAZ_WALK, 56, 56, 8);
        Spaz_run = SpriteSheet(PATH_SPAZ_JUMP,56, 56, 12);
        Spaz_jump = SpriteSheet(PATH_SPAZ_JUMP, 56, 56, 12);
        Spaz_fall = SpriteSheet(PATH_SPAZ_FALL,56, 56, 3);
        Spaz_shoot = SpriteSheet(PATH_SPAZ_SHOOT, 56, 56, 6);
        Spaz_specialAtack = SpriteSheet(PATH_SPAZ_SPECIAL, 56, 56, 12);
        Spaz_damaged = SpriteSheet(PATH_SPAZ_DAMAGED, 56, 56, 11);
        Spaz_intoxicatedIdle = SpriteSheet(PATH_SPAZ_INTOXICATED_IDLE, 56, 56, 8);
        Spaz_intoxicatedWalk = SpriteSheet(PATH_SPAZ_INTOXICATED_WALK,56, 56, 12);
        Spaz_death = SpriteSheet(PATH_SPAZ_DEATH, 96, 96, 26);

        //Lori
        Lori_idle = SpriteSheet(PATH_LORI_IDLE,56, 56, 8);
        Lori_walk = SpriteSheet(PATH_LORI_WALK,56, 56, 8);
        Lori_run = SpriteSheet(PATH_LORI_RUN, 64, 56, 8);
        Lori_jump = SpriteSheet(PATH_LORI_JUMP,56, 56, 13);
        Lori_fall = SpriteSheet(PATH_LORI_FALL,56, 56, 4);
        Lori_shoot = SpriteSheet(PATH_LORI_SHOOT,56, 56, 7);
        Lori_specialAtack = SpriteSheet(PATH_LORI_SPECIAL,56, 56, 10);
        Lori_damaged = SpriteSheet(PATH_LORI_DAMAGED,56, 56, 11);
        Lori_intoxicatedIdle = SpriteSheet(PATH_LORI_INTOXICATED_IDLE,56, 56, 12);
        Lori_intoxicatedWalk = SpriteSheet(PATH_LORI_INTOXICATED_WALK,56, 56, 12);
        Lori_dying = SpriteSheet(PATH_LORI_DYING,60, 60, 20);
        Lori_death = SpriteSheet(PATH_LORI_DEATH,60, 60, 3);

        inicializado = true;
    }
}