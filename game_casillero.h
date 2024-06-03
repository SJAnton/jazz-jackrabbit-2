#ifndef GAME_CASILLERO_H
#define GAME_CASILLERO_H

#include "game_terreno.h"
#include "game_object.h"

#include <set>
#include <memory>
#include <algorithm>



class Casillero {
public:
    bool bloqueado; // si es true ningun objeto puede entrar
    bool vacio;
    //Contiene?
    bool player = false;
    bool enemigo = false;
    bool item = false;
    bool proyectil = false;
    // En general, en un casillero habrá solo un objeto o ninguno. 
    // Pero puede sumarse algun otro objeto que haga movimientos (personajes, proyectiles).
//    std::set<std::shared_ptr<GameObject>> gameObjects; // lista de objetos que están ocupando el casillero

    /**
     * me di cuenta de que guardarse los gameobjects en realidad no es necesario.
     * Solo sirve para poder mostrar todo en la consola, pero es al pedo.
     * Las colisiones se detectan de otra forma.
    */

public:
    Casillero() : bloqueado(false), vacio(true){};
    //Casillero(const bool &bloqueado);

  /*  void addObject(std::shared_ptr<GameObject> obj) {
        gameObjects.insert(obj);
        vacio = false;
    }
    void removeObject(std::shared_ptr<GameObject> obj) {
        gameObjects.erase(obj);
        if (gameObjects.size() == 0)
            vacio = true;
    }
    */
    void bloquear() {bloqueado = true;};

    bool estaBloqueado() {return bloqueado;};

    bool estaVacio() {return vacio;};

    void addObject(TypeGameObject type) {
        switch (type)
        {
        case  Player: player = true;
            break;
        case Collected: item = true;
            break;
        case Enemy: enemigo = true;
            break;
        case Proyectil: proyectil = true;
            break;
        default:
            break;
        }
        vacio = false;
    }
    void removeObject(TypeGameObject type) {
        switch (type)
        {
        case  Player: player = false;
            break;
        case Collected: item = false;
            break;
        case Enemy: enemigo = false;
            break;
        case Proyectil: proyectil = false;
            break;
        default:
            break;
        }
        if (!player && !item && !enemigo && !proyectil)
            vacio = true;
    }
    /*bool estaElObjeto(std::shared_ptr<GameObject> gameObject) {
        auto aux = gameObjects.find(gameObject);
        return aux != gameObjects.end();
    }
    */
    
};

#endif //GAME_CASILLERO_H
