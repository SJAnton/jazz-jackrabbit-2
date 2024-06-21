#include <iostream>

#include "game_mundo.h"
#include "game_casillero.h"
#include "game_coordenada.h"


#define FILAS 30
#define COLUMNAS 30

std::vector<std::vector<Casillero>> GameMundo::casilleros = std::vector<std::vector<Casillero>>(30 * MULTIPLCADOR_CASILLERO, std::vector<Casillero>(30 * MULTIPLCADOR_CASILLERO));

//constructores
GameMundo::GameMundo(std::vector<std::shared_ptr<ObjectPlayer>> players, 
              std::vector<std::shared_ptr<ObjectEnemy>> &enemigos,
              std::vector<ObjectCollected> &itemsRecolectables) :
    filas(FILAS * MULTIPLCADOR_CASILLERO), 
    columnas(COLUMNAS * MULTIPLCADOR_CASILLERO), 
    players(players), enemigos(enemigos), 
    itemsRecolectables(itemsRecolectables)
{
    TileMap tileMap =  TileMap::getLevel_1();
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; ++j) { //Cargo los casilleros solidos
            if (tileMap.terreno[i][j].is_solid()) {
                CoordenadaBloque coordenada(j, i); //bloqueo las coordenadas correspondientes a un tile solido
                bloquearCasilleros(coordenada);
            }
            
        }
    }
    
}

void GameMundo::addPlayer(std::shared_ptr<ObjectPlayer> playerPtr, Coordenada position) {
    
    players.push_back(playerPtr);
    playerPtr->setPosition(position);
}

void GameMundo::addItem(ObjectCollected &&item, const Coordenada &pos) {
    
    //auto objPtr = std::make_shared<ObjectCollected>(item);
    itemsRecolectables.push_back(item);
    itemsRecolectables.back().setPosition(pos);   
}

void GameMundo::addProjectile(ObjectProjectile &&projectile) {
    proyectiles.push_back(projectile);
}

void GameMundo::addEnemy(std::shared_ptr<ObjectEnemy> enemyPtr, Coordenada position) {
    enemigos.push_back(enemyPtr);
    enemyPtr->setPosition(position);
}


void GameMundo::aplicarGravedad() {
    for (auto &player : players) {
        player->fall();
    }
    for (auto &enemy : enemigos) {
        enemy->fall();
    }
}

// ---------------
//   COLISIONES
// ---------------

void GameMundo::chequearColisionesItems() {
    for (auto it = itemsRecolectables.begin(); it != itemsRecolectables.end(); ) {
        std::vector<Coordenada> areaObj = it->coordenadasOcupadas();
        bool itemRecolectado = false;
        for (Coordenada &c : areaObj) { // por cada coordenada ocupada del item...
            if (it->isCollected()) {
                it = itemsRecolectables.erase(it); // elimina el item y actualiza el iterador
                itemRecolectado = true;
                break; // Pasa al siguiente item
            }
            for (auto &p : players) { // por cada player
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
        for (Coordenada &c : areaObj) { // por cada coordenada ocupada del proyectil...
            if (it->is_exploded()) {
                std::cout << "Proyectil destruido" << std::endl;
                it = proyectiles.erase(it); // elimina el proyectil y actualiza el iterador
                hubo_colision = true;
                break; // Pasa al siguiente proyectil
            }
            for (auto &p : players) { // por cada player
                if (p->isInside(c)) {
                    int damage = it->explode();
                    p->take_damage(damage);
                    break; // pasa a la siguiente coordenada
                }
            }
            for (auto &e : enemigos) { // por cada enemigo
                if (e->isInside(c)) {
                    int damage = it->explode();
                    e->take_damage(damage);
                    break; // pasa a la siguiente coordenada
                }
            }
        }
        if (!hubo_colision) {
            ++it; // si no se ha eliminado el proyectil, avanza el iterador
        }
    }
}

void GameMundo::chequearColisionesEnemies() {
    for (auto &e : enemigos) {
        std::vector<Coordenada> areaObj = e->coordenadasOcupadas();
        for (Coordenada &c : areaObj) {
            for (auto &p : players) {
                if (p->isInside(c)) {
                    e->attack();
                    int damage = e->get_damage();
                    p->take_damage(damage);
                    break;
                }
            }
        }
    }
}

void GameMundo::chequearColisiones() {
    chequearColisionesItems();
    chequearColisionesProyectiles();
    chequearColisionesEnemies();
}

//Es llamada por el gameloop
void GameMundo::update() {
    temporizador--;
    aplicarGravedad();
    chequearColisiones();

    for (auto &p : proyectiles) {
        p.move_x_pos();
    }
    for (auto &e : enemigos) {
        e->walk();
    }
    //manejarComandos();
}

// Metodos privados


void GameMundo::bloquearCasilleros(const CoordenadaBloque &bloque) {
    int x = bloque.x * MULTIPLCADOR_CASILLERO;
    int y  = bloque.y * MULTIPLCADOR_CASILLERO;

    for (int i = y; i < y+MULTIPLCADOR_CASILLERO; ++i) {
        for (int j = x; j < x+MULTIPLCADOR_CASILLERO; ++j) {
            casilleros[i][j].bloquear();
        }        
    }
}

std::vector<InfoProyectil> GameMundo::getInfoProyectiles() {
    std::vector<InfoProyectil> projectile_data;
    for (auto &proyectil : proyectiles) {
        if (proyectil.is_exploded())
            continue;
        InfoProyectil info = proyectil.getInfo();
        projectile_data.push_back(info);
    }
    return projectile_data;
}
