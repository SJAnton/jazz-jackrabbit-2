#include "sprites_players.h"
#include "sprites_paths.h"

//Tengo que declararlos aca porque son static

// Jazz
SpriteSheet SpritesPlayers::Jazz_idle;
SpriteSheet SpritesPlayers::Jazz_walk;
SpriteSheet SpritesPlayers::Jazz_run;
SpriteSheet SpritesPlayers::Jazz_jump;
SpriteSheet SpritesPlayers::Jazz_fall;
SpriteSheet SpritesPlayers::Jazz_shoot;
SpriteSheet SpritesPlayers::Jazz_specialAtack;
SpriteSheet SpritesPlayers::Jazz_damaged;
SpriteSheet SpritesPlayers::Jazz_intoxicatedIdle;
SpriteSheet SpritesPlayers::Jazz_intoxicatedWalk;
SpriteSheet SpritesPlayers::Jazz_dying;
SpriteSheet SpritesPlayers::Jazz_death;

// Spaz
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
SpriteSheet SpritesPlayers::Spaz_dying;
SpriteSheet SpritesPlayers::Spaz_death;

// Lori
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
        //Jazz (NO IMPLEMENTDO, reemplazar despues)
        Jazz_idle = SpriteSheet(PATH_JAZZ_IDLE, 56, 56, 14);
        Jazz_walk = SpriteSheet(PATH_JAZZ_WALK, 57, 56, 8);
        Jazz_run = SpriteSheet(PATH_JAZZ_RUN,72, 72, 4);
        Jazz_jump = SpriteSheet(PATH_JAZZ_JUMP, 56, 56, 12);
        Jazz_fall = SpriteSheet(PATH_JAZZ_FALL,56, 56, 3);
        Jazz_shoot = SpriteSheet(PATH_JAZZ_SHOOT, 56, 56, 7);
        Jazz_specialAtack = SpriteSheet(PATH_JAZZ_SPECIAL, 56, 64, 12);
        Jazz_damaged = SpriteSheet(PATH_JAZZ_DAMAGED, 72, 72, 9);
        Jazz_intoxicatedIdle = SpriteSheet(PATH_JAZZ_INTOXICATED_IDLE, 56, 56, 8);
        Jazz_intoxicatedWalk = SpriteSheet(PATH_JAZZ_INTOXICATED_WALK,64, 64, 12);
        Jazz_death = SpriteSheet(PATH_JAZZ_DEATH, 88, 88, 20);
        
        //Spaz
        Spaz_idle = SpriteSheet(PATH_SPAZ_IDLE, 56, 56, 6);
        Spaz_walk = SpriteSheet(PATH_SPAZ_WALK, 56, 56, 8);
        Spaz_run = SpriteSheet(PATH_SPAZ_RUN, 56, 56, 4);
        Spaz_jump = SpriteSheet(PATH_SPAZ_JUMP, 56, 56, 12);
        Spaz_fall = SpriteSheet(PATH_SPAZ_FALL,56, 56, 3);
        Spaz_shoot = SpriteSheet(PATH_SPAZ_SHOOT, 56, 56, 6);
        Spaz_specialAtack = SpriteSheet(PATH_SPAZ_SPECIAL, 56, 56, 12);
        Spaz_damaged = SpriteSheet(PATH_SPAZ_DAMAGED, 56, 56, 11);
        Spaz_intoxicatedIdle = SpriteSheet(PATH_SPAZ_INTOXICATED_IDLE, 56, 56, 8);
        Spaz_intoxicatedWalk = SpriteSheet(PATH_SPAZ_INTOXICATED_WALK,56, 56, 12);
        Spaz_dying = SpriteSheet(PATH_SPAZ_DYING, 56, 56, 13);
        Spaz_death = SpriteSheet(PATH_SPAZ_DEATH, 56, 56, 7);

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