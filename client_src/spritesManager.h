#ifndef SPRITES_MANAGER_H
#define SPRITES_MANAGER_H

#include "../common_src/constantes.h"
#include "sprite_object.h"
#include "spritesheet.h"
//#include "spritesheetPlayer.h"
#include "sprite_player.h"
#include "sprites_players.h"

#include <list>
#include <vector>

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
    /*SpriteSheetPlayer playerSpaz_idle;
    SpriteSheetPlayer playerSpaz_walk;
    SpriteSheetPlayer playerSpaz_jump;
    SpriteSheetPlayer playerSpaz_shoot;
    SpriteSheetPlayer playerSpaz_specialAtack;
    SpriteSheetPlayer playerSpaz_death;
*/
    std::list<SpritePlayer> players;
    std::vector<EstadosPlayer> estadosPlayers;

    bool playerInvertido = false;

private: 
    //void setPlayerJazz(SpriteSheet &player, EstadosPlayer estado);
    //void setPlayerSpaz(SpriteSheet &player, EstadosPlayer estado);
    //void setPlayerLori(SpriteSheet &player, EstadosPlayer estado);
    SpritePlayer& getPlayer(unsigned int n);


public:
    SpritesManager();

    //constructor que recibe la cantidad maxima de jugadores y el tipoPlayer de cada uno
    //(Todavia no está implementado).
    SpritesManager(int countPlayers, TipoPlayer tipos[]);

    //EstadosPlayer getEstadoPlayer(unsigned int numero);

    //modifica el spritesheet por otro que corresponda al estado nuevo, cambiando de animacion
    //void setEstadoPlayer(unsigned int numero, EstadosPlayer estado);
    void flipPlayer(unsigned int numero, bool invertirSprite);

    //modifica al player n pasando al siguiente frame del spritesheet
    //void nextFramePlayer(unsigned int n);

    void updatePlayer(unsigned int n, const EstadosPlayer &estado, const Position &pos);
    //pinta en la pantalla en la posicion recibida.
    //(para despues: pensar si es necesario usar .renderizarEn(x, y) o alcanza solo con  .renderizar())
    void renderizarPlayerEn(unsigned int n, int x, int y);

    void renderizarFondo();

    //~SpritesManager();
};


#endif
