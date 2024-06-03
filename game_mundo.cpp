#include "game_mundo.h"
#include <iostream>


//constructores
GameMundo::GameMundo() :
    terreno(15, 15), 
    filas(15*MULTIPLCADOR_CASILLERO), columnas(15*MULTIPLCADOR_CASILLERO),
    casilleros(filas, std::vector<Casillero>(columnas))
{

}
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


void GameMundo::addPlayer(ObjectPlayer &&player, Coordenada position) {
    int x = position.x;
    int y = position.y;

    auto playerPtr = std::make_shared<ObjectPlayer>(player);
    players.push_back(playerPtr);
    playerPtr->setPosition(position);


    //para ver en pantalla. No es necesario
    cargarCasilleros(playerPtr);
    CoordenadaBloque bloque = position.toBloque();
    terreno.setValor(bloque.y, bloque.x, PLAYER1);
}

void GameMundo::addItem(ObjectCollected &&item, const Coordenada &pos) {
    int x = pos.x;
    int y = pos.y;

    auto objPtr = std::make_shared<ObjectCollected>(item);

    items.push_back(objPtr);
    objPtr->setPosition(pos);
    cargarCasilleros(objPtr);
    CoordenadaBloque bloque = pos.toBloque();
    terreno.setValor(bloque.y, bloque.x, MONEDA);
    std::cout << "item agregado"<< std::endl;
   
}

void GameMundo::aplicarGravedad() {
    for (auto& playerPtr : players) {
        int y_down = playerPtr->getPositionEnd().y + 1;
        int x = playerPtr->getPosition().x;
        int x_max = playerPtr->getPositionEnd().x;

        std::vector<Coordenada> coordenadasAbajo = playerPtr->coordenadasAbajo();
        if (casilleros[y_down][x].estaBloqueado() || casilleros[y_down][x_max].estaBloqueado()) {
            // Colisión con pared
            std::cout << "pared abajo" << std::endl;
            continue;  // Pasar al siguiente jugador
        }

        descargarCasilleros(playerPtr);
        playerPtr->fall();
        cargarCasilleros(playerPtr);
    }


}

void GameMundo::MoverPlayer(int id, Direcciones direccion) {
    //Obtener el player con ese id ...

    auto playerPtr = players.back();

    if (direccion == Left){
        int x_left = playerPtr->getPosition().x - 1;
        int y = playerPtr->getPosition().y;
        int y_max = playerPtr->getPositionEnd().y;

        if (casilleros[y][x_left].estaBloqueado() || casilleros[y_max][x_left].estaBloqueado()) {
            //Colison con pared
            std::cout << "pared a la izquierda" << std::endl;
            return;
        }
    } else if (direccion == Right) {
        int x_right = playerPtr->getPositionEnd().x + 1;
        int y = playerPtr->getPosition().y;
        int y_max = playerPtr->getPositionEnd().y;

        if (casilleros[y][x_right].estaBloqueado() || casilleros[y_max][x_right].estaBloqueado()) {
            //Colison con pared
            std::cout << "pared a la derecha" << std::endl;
            return;
        }
    }
    
    descargarCasilleros(playerPtr);
    playerPtr->walk(direccion);
    aplicarGravedad();
    cargarCasilleros(playerPtr);

    //std::cout << "position x " << playerPtr->getPosition().x << std::endl;
    CoordenadaBloque bloque = playerPtr->getPosition().toBloque();
    terreno.setValor(bloque.y, bloque.x, PLAYER2);
}

//Es llamada por el gameloop
void GameMundo::update() {
    temporizador--;
    aplicarGravedad();

    manejarComandos();

    //chequear colision de items
    for (auto item : items) {
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

    //chequear colision de enemigos

    //chequear colision de proyectiles

}

// Metodos privados


void GameMundo::manejarComandos() { 
    //try_pop()...
}



void GameMundo::bloquearCasilleros(const CoordenadaBloque &bloque) {
    int x = bloque.x * MULTIPLCADOR_CASILLERO;
    int y  = bloque.y * MULTIPLCADOR_CASILLERO;

    for (int i = y; i < y+MULTIPLCADOR_CASILLERO; i++) {
        for (int j = x; j < x+MULTIPLCADOR_CASILLERO; j++) {
            casilleros[i][j].bloquear();
        }        
    }
}



//para mostrar en pantalla

void GameMundo::printTerreno() {
    std::cout << terreno.toString();   
}


void GameMundo::printCasilleros2() {//eliminar
    std::string resultado;
    for (int i = 0; i < filas; i++) {
        for (size_t j = 0; j < columnas; j++) {
            resultado += " ";
            if (casilleros[i][j].estaBloqueado())
                resultado += "X";
            else if (!casilleros[i][j].estaVacio()) {
                if (casilleros[i][j].player) {
                    resultado += PLAYER1;
                }
                if (casilleros[i][j].item) {
                    resultado += MONEDA;
                }
            }
            else 
                resultado += " ";
            }
            resultado += " ";

            resultado += '\n';
    }
    std::cout << resultado;
}


void GameMundo::cargarCasilleros(std::shared_ptr<GameObject> gameObject) {// eliminar
    Coordenada c = gameObject->getPositionEnd();
    int x = gameObject->getPosition().x;
    int y  = gameObject->getPosition().y;

    for (int i = y; i <= c.y; i++) {
        for (int j = x; j <= c.x; j++) {
            casilleros[i][j].addObject(gameObject->getType());
            
        }        
    }
}


void GameMundo::descargarCasilleros(std::shared_ptr<GameObject> gameObject) {//eliminar

    Coordenada c = gameObject->getPositionEnd();
    int x =gameObject->getPosition().x;
    int y  = gameObject->getPosition().y;

    for (int i = y; i <= c.y; i++) {
        for (int j = x; j <= c.x; j++) {
            casilleros[i][j].removeObject(gameObject->getType());
        }        
    }
}
