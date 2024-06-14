#include "game_mundo.h"
#include <iostream>


#include "game_casillero.h"
#include "game_coordenada.h"

std::vector<std::vector<Casillero>> GameMundo::casilleros = std::vector<std::vector<Casillero>>(15 * MULTIPLCADOR_CASILLERO, std::vector<Casillero>(15 * MULTIPLCADOR_CASILLERO));

//constructores
GameMundo::GameMundo(std::vector<std::shared_ptr<ObjectPlayer>> players, 
              std::vector<ObjectEnemy> &enemigos,
              std::vector<ObjectCollected> &itemsRecolectables, 
              std::vector<ObjectProjectile> &proyectiles) :
    filas(15*MULTIPLCADOR_CASILLERO), 
    columnas(15*MULTIPLCADOR_CASILLERO), 
    players(players), enemigos(enemigos), 
    itemsRecolectables(itemsRecolectables), 
    proyectiles(proyectiles)
{
   for (int j = 0; j < 15; ++j) { //Cargo los casilleros solidos (HARDCODEADO)
        CoordenadaBloque coord(j, 4); //bloqueo la fila 4
        bloquearCasilleros(coord);
    }
}

/*
GameMundo::GameMundo(Terreno &&_terreno) : 
    terreno(_terreno),
    filas(_terreno.getFilas()*MULTIPLCADOR_CASILLERO),
    columnas(_terreno.getColumnas()*MULTIPLCADOR_CASILLERO),
    casilleros(filas, std::vector<Casillero>(columnas))
{
    for (int i=0; i< terreno.getFilas(); i++){
        for (int j=0; j< terreno.getColumnas(); j++) {
            if (terreno.getValor(i, j) == PARED) {
                bloquearCasilleros(CoordenadaBloque(j, i));
            }
        }
    }

}
*/


void GameMundo::addPlayer(std::shared_ptr<ObjectPlayer> playerPtr, Coordenada position) {
    
    players.push_back(playerPtr);
    playerPtr->setPosition(position);
}

void GameMundo::addItem(ObjectCollected &&item, const Coordenada &pos) {
    
    //auto objPtr = std::make_shared<ObjectCollected>(item);
    itemsRecolectables.push_back(item);
    itemsRecolectables.back().setPosition(pos);   
}


void GameMundo::aplicarGravedad() {
    for (auto player : players) {
        player->fall();
    }
}

//
//   COLISIONES
// ---------------

void GameMundo::chequearColisionesItems() {
    for (auto it = itemsRecolectables.begin(); it != itemsRecolectables.end(); ) {
        std::vector<Coordenada> areaObj = it->coordenadasOcupadas();
        bool itemRecolectado = false;
        for (Coordenada c : areaObj) { // por cada coordenada ocupada del item...
            if (it->isCollected()) {
                std::cout << "item recolectado" << std::endl;
                it = itemsRecolectables.erase(it); // elimina el item y actualiza el iterador
                itemRecolectado = true;
                break; // Pasa al siguiente item
            }
            for (auto p : players) { // por cada player
                if (p->isInside(c)) {
                    int pts = it->recolectar();
                    // Si es una moneda o diamante...
                    if (it->getTipoRecolectable() == Moneda || it->getTipoRecolectable() == Diamante)
                        p->add_points(pts);
                    else if (it->getTipoRecolectable() == Zanahoria)
                        p->add_hearts(pts);
                    else if (it->getTipoRecolectable() == Municion)
                        p->pick_up_ammo(pts);
                    break; // pasa a la siguiente coordenada
                }
            }
        }
        if (!itemRecolectado) {
            ++it; // si no se ha eliminado el item, avanza el iterador
        }
    }
}

void GameMundo::chequearColisionesProyectiles() {
    for (auto it = proyectiles.begin(); it != proyectiles.end(); ) { //por cada proyectil
        std::vector<Coordenada> areaObj = it->coordenadasOcupadas();
        bool hubo_colision = false;
        for (Coordenada c : areaObj) { // por cada coordenada ocupada del proyectil...
            if (it->is_exploded()) {
                std::cout << "Proyectil destruido" << std::endl;
                it = proyectiles.erase(it); // elimina el proyectil y actualiza el iterador
                hubo_colision = true;
                break; // Pasa al siguiente proyectil
            }
            for (auto p : players) { // por cada player
                if (p->isInside(c)) {
                    int damage = it->explode();
                    p->take_damage(damage);
                    break; // pasa a la siguiente coordenada
                }
            }
            for (auto e : enemigos) { // por cada enemigo
                if (e.isInside(c)) {
                    int damage = it->explode();
                    e.take_damage(damage);
                    break; // pasa a la siguiente coordenada
                }
            }
        }
        if (!hubo_colision) {
            ++it; // si no se ha eliminado el proyectil, avanza el iterador
        }
    }
}

void GameMundo::chequearColisiones() {
    chequearColisionesItems();
    chequearColisionesProyectiles();
    
}



//Es llamada por el gameloop
void GameMundo::update() {
    temporizador--;
    aplicarGravedad();
    chequearColisiones();

    //manejarComandos();

    //chequear colision de items
    /*for (auto item : items) {
        std::vector<Coordenada> areaObj = item->coordenadasOcupadas();
        for (Coordenada c : areaObj) {
            if (item->isCollected()) {
                descargarCasilleros(item);
                //items.pop(item);
                break;//Pasa al siguiente item
            }
            for (auto p : players) {
                if (p->isInside(c)) {
                    int pts = item->recolectar();
                    //Si es una moneda o diamante...
                        p->add_points(pts);
                    //Si es una zanahora...
                        //p->...(pts);
                    
                    //Si es una muncion...
                        //p->...(pts);
                    break; //pasa a la siguiente coordenada
                }
            }
        }
    }
    */

    //chequear colision de enemigos

    //chequear colision de proyectiles

}

// Metodos privados


void GameMundo::bloquearCasilleros(const CoordenadaBloque &bloque) {
    int x = bloque.x * MULTIPLCADOR_CASILLERO;
    int y  = bloque.y * MULTIPLCADOR_CASILLERO;

    for (int i = y; i < y+MULTIPLCADOR_CASILLERO; i++) {
        for (int j = x; j < x+MULTIPLCADOR_CASILLERO; j++) {
            casilleros[i][j].bloquear();
        }        
    }
}


