#ifndef SPRITES_MANAGER_H
#define SPRITES_MANAGER_H

#include "../../common_src/constantes.h"
#include "sprite_object.h"
#include "spritesheet.h"
//#include "spritesheetPlayer.h"
#include "sprite_player.h"
#include "sprites_players.h"
#include "sprites_paths.h"
#include "button_partida.h"
#include "button_character.h"
#include <list>
#include <vector>

//carga todos los sprites que se van a utilizar a lo largo de todo el juego
class SpritesManager
{
private:
    //MENU
    SpriteObject botonPlay;
    SpriteObject titulo;

    //SeleccionarPartida
    std::list<ButtonPartida> botones_partidas;
    std::list<ButtonCharacter> botones_character;
    //SpriteObject letras;
    SDL_Texture* fontTexture;

    //SeleccionPlayer
    SpriteObject character_spaz;
    SpriteObject character_jazz;
    SpriteObject character_lori;

    //terreno 
    SpriteObject fondo;//Podria ser una imagen grande
    SpriteObject piso;
    SpriteObject pisoIzq;
    SpriteObject PisoDer;
    SpriteObject pisoDiagonalIzq;
    SpriteObject pisoDiagonalDer;
    SpriteObject pisoBloque;

    SpriteSheet moneda;
    SpriteSheet gema;
    SpriteSheet zanahoria;

    std::list<SpritePlayer> players;
    std::vector<EstadosPlayer> estadosPlayers;
 
    bool playerInvertido = false;

private: 
    SpritePlayer& getPlayer(unsigned int n);


public:
    SpritesManager();

    //constructor que recibe la cantidad maxima de jugadores y el tipoPlayer de cada uno
    //(Todavia no está implementado).
    SpritesManager(int countPlayers, TipoPlayer tipos[]);

    void renderizarMenu();

    void inicializarBotonesPartidas(const std::vector<int> &id_partidas);
    std::list<ButtonPartida> getBotonesPartidas();
    void renderizarBotonesPartidas();

    void inicializarBotonesCharacter();
    std::list<ButtonCharacter> getBotonesCharacter();
    void renderizarBotonesCharacter();
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
    void renderizarPlayer(unsigned int n);

    void renderizarFondo();

    void renderizarItemEn(const TipoRecolectable &tipo, int x, int y);
    void updateItems();
    //~SpritesManager();
};


#endif
