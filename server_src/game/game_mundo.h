#ifndef GAME_MUNDO_H
#define GAME_MUNDO_H

//#include "game_terreno.h"
#include "game_casillero.h"
#include "game_coordenada.h"
#include "GameObjects/game_object.h"
#include "GameObjects/Players/game_object_player.h"
#include "GameObjects/Collected/game_object_collected.h"
#include "GameObjects/Enemies/game_object_enemy.h"
#include "GameObjects/Enemies/enemy_rat.h"

#include "GameObjects/Projectile/game_object_projectile.h"
#include "../server_character_map.h"

#include <list>
#include <vector>

class GameMundo {
private:
    int temporizador = 180;
    int filas;
    int columnas;

    // El terreno se puede pensar como los casilleros simplificados.
    //TileMap TileMap;
    std::vector<std::shared_ptr<ObjectPlayer>> players; //lista de los players
    std::vector<ObjectEnemy> &enemigos;
    std::vector<ObjectCollected> &itemsRecolectables;
    std::vector<ObjectProjectile> &proyectiles;


public:
    /** ACLARACION sistema de coordenadas y casilleros
     * -----------------------------------
     * El eje X con sentido positivo a la derecha y el eje Y con con sentido positivo hacia abajo 
     * (el (0,0) en  la esquina superior izquierda).
     * No va a haber coordenadas negativas.
     * 
     * 1 bloque del terreno (tile) equivaldrá a (64x64) unidades del sistema de coordenadas del juego (casilleros).
     * Es decir que por ej. 
     * - El bloque de terreno (0,0) cubre los casilleros del rectangulo de vertices ((0,0), (0, 63), (63, 0), (63, 63))
     * - las coordenadas (70,130) pertenecen al bloque de terreno (1,2)  
     * Para saber a que bloque pertenece una coordenada simplemente se debe dividir por 64 
     * y tomar el valor entero del resutado.
     * 
     * Si un GameObject se ubica en la coordenada (10, 10) y su tamaño es de 4x3,
     * entonces estará ocupando tambien los casilleros siguientes. 
     * De la forma:
     *              09 10 11 12 13 14
     *           09  .  .  .  .  .  .
     *           10  .  X  x  x  x  .
     *           11  .  x  x  x  x  .
     *           12  .  x  x  x  x  .
     *           13  .  .  .  .  .  . 
     * 
     * nota:
     * La coordenada (20, 30) equivale al Casillero [30][20], (y = fila 30, x = col 20)
     * 
    */
    static std::vector<std::vector<Casillero>> casilleros;

public:
    GameMundo(std::vector<std::shared_ptr<ObjectPlayer>> players, 
              std::vector<ObjectEnemy> &enemigos,
              std::vector<ObjectCollected> &itemsRecolectables, 
              std::vector<ObjectProjectile> &proyectiles);

    //Recibe el terreno ya creado
    //GameMundo(Terreno &&terreno);

    void addItem(ObjectCollected &&item, const Coordenada &position);
    void addPlayer(std::shared_ptr<ObjectPlayer>, Coordenada position);

    // Avanza una iteracion en el tiempo, aplica la gravedad a todos los objetos con peso
    // Chequea todas las colisiones de los recolectables, proyectiles, etc.
    void update();

private:
    //void cargarMapa(const Terreno &terreno);

    //bloquea todos los casilleros que pertenecen al tile
    void bloquearCasilleros(const CoordenadaBloque &bloque);

    void aplicarGravedad();
    
    /**
     * Chequea si un player esta dentro de algun item recolectable (si esta colisionando) 
     * y en ese caso lo recolecta, aplicando la accion que corresponda sobre el player, 
     * y eliminando el item del vector.
    */
    void chequearColisionesItems();

    /**
     * Chequea si un proyectil está dentro de un player o de un enemigo
     * y en ese caso explota, dañando al personaje con el que colisionó 
    */
    void chequearColisionesProyectiles();
    void chequearColisionesEnemies();

    void chequearColisiones();
    
    
};

#endif // GAME_MUNDO_H
