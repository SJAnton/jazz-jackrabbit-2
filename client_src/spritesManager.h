#ifndef SPRITES_MANAGER_H
#define SPRITES_MANAGER_H

#include "../common_src/constantes.h"
#include "sprite_object.h"
#include "spritesheet.h"
#include "spritesheetPlayer.h"

#include <list>
//carga todos los sprites que se van a utilizar a lo largo de todo el juego

class SpritesManager
{
private:
    SpriteObject fondo;

    //terreno
    SpriteObject piso;
    SpriteObject pisoIzq;
    SpriteObject PisoDer;
    SpriteObject pisoDiagonalIzq;
    SpriteObject pisoDiagonalDer;
    SpriteObject pisoBloque;

    //Spritesheets Players
    SpriteSheetPlayer playerSpaz_idle;
    SpriteSheetPlayer playerSpaz_walk;
    SpriteSheetPlayer playerSpaz_specialAtack;

    std::list<SpriteSheetPlayer> players;

private: 
    void setPlayerJazz(SpriteSheet &player, EstadosPlayer estado);
    void setPlayerSpaz(SpriteSheet &player, EstadosPlayer estado);
    void setPlayerLori(SpriteSheet &player, EstadosPlayer estado);
    SpriteSheetPlayer& getPlayer(unsigned int n);


public:
    SpritesManager(SDL_Renderer *renderer);

    //recibe la cantidad maxima de jugadores y el tipoPlayer de cada uno
    //(Todavia no está implementado).
    SpritesManager(SDL_Renderer *renderer, int countPlayers, TipoPlayer tipos[]);

    //modifica el spritesheet por otro que corresponda al estado nuevo, cambiando de animacion
    void setPlayer(unsigned int numero, EstadosPlayer estado);

    //modifica al player n pasando al siguiente frame del spritesheet
    void nextFramePlayer(unsigned int n);

    //pinta en la pantalla en la posicion recibida.
    //(para despues: pensar si es necesario usar .renderizarEn(x, y) o alcanza solo con  .renderizar())
    void renderizarPlayerEn(unsigned int n, int x, int y);

    void renderizarFondo();

    //~SpritesManager();
};


#endif
