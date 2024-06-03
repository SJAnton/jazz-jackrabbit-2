#ifndef GAME_MUNDO_H
#define GAME_MUNDO_H

#include "game_terreno.h"
#include "game_casillero.h"
#include "game_coordenada.h"
#include "game_object.h"
#include "game_object_collected.h"
#include "game_object_player.h"

#include <list>
#include <vector>

class GameMundo {
private:
    int temporizador = 180; // en seg.
    int filas;
    int columnas;

    // El terreno se puede pensar como los casilleros simplificados ()
    Terreno terreno;

    /** ACLARACION sistema de coordenadas y casilleros
     * -----------------------------------
     * El eje X con sentido positivo a la derecha y el eje Y con con sentido positivo hacia abajo 
     * (el (0,0) en  la esquina superior izquierda).
     * No va a haber coordenadas negativas.
     * 
     * 1 bloque del terreno equivaldrá a (16x16) unidades del sistema de coordenadas.
     * Es decir que por ej. 
     * - las coordenadas (0,0) pertenecen al bloque de terreno (0,0)  
     * - las coordenadas (15,15) pertenecen al bloque de terreno (0,0)
     * - las coordenadas (15,16) pertenecen al bloque de terreno (0,1)
     * - las coordenadas (20,34) pertenecen al bloque de terreno (1,2)
     * Para saber a que bloque pertenece una coordenada simplemente se debe dividir por 16 
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
    std::vector<std::vector<Casillero>> casilleros;

    std::list<std::shared_ptr<ObjectPlayer>> players; //si se puede, sacar shared ptr
    std::list<std::shared_ptr<ObjectCollected>> items;
    //std::list<ObjectProyectil> proyectiles;
    //std::list<ObjectProyectil> enemigos;

    //queue de comandosRecibidos

private:
    //void cargarMapa(const Terreno &terreno);

    //Agrega el gameobject a los casilleros que le corresponden a este
    void cargarCasilleros(std::shared_ptr<GameObject> gameObject);

    // quita el gameobject de los casilleros que ocupa este
    void descargarCasilleros(std::shared_ptr<GameObject> gameObject);

    //bloquea todos los casilleros que pertenecen al bloque
    void bloquearCasilleros(const CoordenadaBloque &bloque);

    void aplicarGravedad();

public:
    GameMundo();

    GameMundo(Terreno &&terreno);

    void addItem(ObjectCollected &&item, const Coordenada &position);

    void addPlayer(ObjectPlayer &&player, Coordenada position);

    void MoverPlayer(int id, Direcciones direccion);//privada


    // Avanza una iteracion en el tiempo
    void update();

    void manejarComandos(); //intenta sacar de la queue algun comando y lo ejecuta

    void printTerreno();

    //para ver desde el server. 
    //void printCasilleros();
    void printCasilleros2(); //ELIMINAR
};

#endif // GAME_MUNDO_H
