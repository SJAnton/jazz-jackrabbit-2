#include "sprites_enemies.h"
#include "sprites_paths.h"

//Bat
SpriteSheet SpritesEnemies::Bat_idle;
SpriteSheet SpritesEnemies::Bat_attack;

//Rat
SpriteSheet SpritesEnemies::Rat_idle;
SpriteSheet SpritesEnemies::Rat_walk;
SpriteSheet SpritesEnemies::Rat_attack;

//Diablo
SpriteSheet SpritesEnemies::Diablo_idle;
SpriteSheet SpritesEnemies::Diablo_attack;
SpriteSheet SpritesEnemies::Diablo_damaged;


bool SpritesEnemies::inicializado = false;

void SpritesEnemies::init() {
    if (!inicializado) {
        //Bat
        Bat_idle = SpriteSheet(PATH_BAT_IDLE, 32, 40, 8);
        Bat_attack = SpriteSheet(PATH_BAT_ATTACK, 72, 48, 8);
        
        //Rat
        Rat_idle = SpriteSheet(PATH_RAT_IDLE, 84, 44, 8);
        Rat_walk = SpriteSheet(PATH_RAT_WALK, 84, 44, 8);
        Rat_attack = SpriteSheet(PATH_RAT_ATTACK, 84, 44, 8);

        //Diablo
        Diablo_idle = SpriteSheet(PATH_DIABLO_IDLE, 64, 64, 13);
        Diablo_attack = SpriteSheet(PATH_DIABLO_ATTACK, 64, 64, 8);
        Diablo_damaged = SpriteSheet(PATH_DIABLO_DAMAGED, 64, 64, 9);

        inicializado = true;
    }
}