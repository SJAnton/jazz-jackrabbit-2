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
    SDL_Texture* fontTexture;//cambiar

    //SeleccionPlayer
    SpriteObject character_spaz;
    SpriteObject character_jazz;
    SpriteObject character_lori;

    //terreno 
    SpriteObject fondo;//Podria ser una imagen grande
    //SpriteTileMap (implementar)
    SpriteObject piso;
    SpriteObject pisoIzq;
    SpriteObject PisoDer;
    SpriteObject pisoDiagonalIzq;
    SpriteObject pisoDiagonalDer;
    SpriteObject pisoBloque;

    //Items recolectables
    SpriteSheet moneda;
    SpriteSheet gema;
    SpriteSheet zanahoria;

    //Players
    std::list<SpritePlayer> players;
    bool playerInvertido = false;// sacar

    //Proyectiles
    SpriteSheet proyectil_0;

    //HUD
    SpriteObject heartIcon;


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

    

    //RENDERIZADORES

    void renderizarPlayerEn(unsigned int n, int x, int y);
    void renderizarPlayer(unsigned int n);

    void renderizarFondo(const Position &posCamara);
    void renderizarTerreno();
    void renderizarItemEn(const TipoRecolectable &tipo, int x, int y);
    void renderizarProyectilEn(const Direcciones &dir, int x, int y);

    // UPDATES
    /**
     * Avanza al siguiente frame de la animacion de todos los items recolectables
    */
    void updateItems();
    /**
     * Avanza al siguiente frame de la animacion de todos los proyectiles
    */
    void updateProyectiles();

    /**
     * Actualiza el player numero 'n'.
     * Se cambia la posicion a la posicion recibida.
     * Si el estado es el mismo que tenia antes, avanza al siguiente frame de la animacion.
     * Si es diferente al que tenia antes, cambia su estado (y su animacion).
     * 
     * nota.
     * Si NO EXISTE el player numero 'n' en SpritesManager, lanza una excepcion
    */
    void updatePlayer(unsigned int n, const EstadosPlayer &estado, const Position &pos);

    /**
     * Actualiza el enemy numero 'n'.
     * Se cambia la posicion a la posicion recibida.
     * Si el estado es el mismo que tenia antes, avanza al siguiente frame de la animacion.
     * Si es diferente al que tenia antes, cambia su estado (y su animacion).
     * 
     * nota.
     * Si NO EXISTE el enemigo numero 'n' en SpritesManager, lanza una excepcion
    */
    void updateEnemy(unsigned int n, const EstadosEnemy &estado, const Position &pos);
    
    //~SpritesManager();
};


#endif
