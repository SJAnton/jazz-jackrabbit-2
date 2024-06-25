#ifndef SPRITES_MANAGER_H
#define SPRITES_MANAGER_H

#include "../../common_src/constantes.h"
#include "sprite_object.h"
#include "spritesheet.h"
//#include "spritesheetPlayer.h"
#include "sprite_player.h"
#include "sprites_players.h"
#include "sprite_enemy.h"
#include "sprites_enemies.h"
#include "sprites_paths.h"
#include "button_partida.h"
#include "button_character.h"
#include "fontManager.h"
#include "../../common_src/tile_map.h"
#include "../../common_src/info_juego.h"
#include "sprites_tile_map.h"
#include <algorithm> 

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
    fontManager font;

    //SeleccionPlayer
    SpriteObject character_spaz;
    SpriteObject character_jazz;
    SpriteObject character_lori;

    //terreno 
    SpritesTileMap spritesTileMap;

    //Items recolectables
    SpriteSheet moneda;
    SpriteSheet gema;
    SpriteSheet zanahoria;
    SpriteSheet municion_1;
    SpriteSheet municion_2;
    SpriteSheet municion_3;
    SpriteSheet municion_4;

    //Players
    std::list<SpritePlayer> players;

    //Enemies
    std::list<SpriteEnemy> enemies;
    //Proyectiles
    SpriteSheet proyectil_0;
    SpriteSheet proyectil_1;
    SpriteSheet proyectil_2;
    SpriteSheet proyectil_3;
    SpriteSheet proyectil_4;

    //HUD
    SpriteObject heartIcon;
    SpriteSheet gun_1;
    SpriteSheet gun_2;
    SpriteSheet gun_3;
    SpriteSheet gun_4;

    //SpriteSheet spazGun;
    //SpriteSheet jazzGun;
    //SpriteSheet loriGun;


private: 
    SpritePlayer& getPlayer(unsigned int n);
    SpriteEnemy& getEnemy(unsigned int n);


public:
    SpritesManager();

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
    //void flipPlayer(unsigned int numero, bool invertirSprite);

    
    void addPlayer(const TipoPlayer &tipo);
    void addEnemy(const TipoEnemy &tipo);

    //RENDERIZADORES

    //void renderizarPlayerEn(unsigned int n, int x, int y);
    void renderizarPlayer(unsigned int n);
    void renderizarEnemigo(unsigned int n);
    void renderizarTerreno(const Position &posCamara);
    void renderizarItemEn(const TipoRecolectable &tipo, int x, int y);
    void renderizarProyectilEn(const Direcciones &dir, TipoArma &tipo,int x, int y);
    void renderizarVidas(int &vidas);
    void renderizarMunicionArma(const TipoArma &tipo, int cantMunicion);
    void renderizarTablaPosiciones(const std::vector<InfoPlayer> players);


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
    void updatePlayer(unsigned int n, const EstadosPlayer &estado, const Position &pos, const Direcciones &dir);

    /**
     * Actualiza el enemy numero 'n'.
     * Se cambia la posicion a la posicion recibida.
     * Si el estado es el mismo que tenia antes, avanza al siguiente frame de la animacion.
     * Si es diferente al que tenia antes, cambia su estado (y su animacion).
     * 
     * nota.
     * Si NO EXISTE el enemigo numero 'n' en SpritesManager, lanza una excepcion
    */
    void updateEnemy(unsigned int n, const EstadosEnemy &estado, const Position &pos, const Direcciones &dir);
    
    void setMapa(const TileMap &tileMap);
    //~SpritesManager();
};


#endif
