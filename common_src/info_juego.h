#ifndef INFO_JUEGO_H
#define INFO_JUEGO_H

#include "constantes.h"
#include "constantes_protocolo.h"

#include <vector>
#include <cstdint>

#define LENGTH_PLAYER_INFO 8
#define LENGTH_ENEMY_INFO 0
#define LENGTH_ITEMS_INFO 0
#define LENGTH_PROYECTIL_INFO 0

// Clase que representa la información de un jugador
class InfoPlayer {
public:
    int id;
    int pos_x;
    int pos_y;
    EstadosPlayer estado;
    int vida;
    int puntos;
    TipoArma arma;
    int muncion;

    InfoPlayer(){};
    InfoPlayer(int id, int x, int y, EstadosPlayer e, int vida, int pts, TipoArma arma, int municion)
        : id(id), pos_x(x), pos_y(y), estado(e), vida(vida), puntos(pts), arma(arma), muncion(municion){}

    std::vector <uint8_t> encode() {
        std::vector <uint8_t> bytes;
        bytes.push_back(id);
        return bytes;
    }
};


class InfoEnemigo {
public:
    int pos_x;
    int pos_y;
    TipoEnemy tipo;
    EstadosEnemy estado;

    InfoEnemigo(int x, int y, TipoEnemy tipo, EstadosEnemy estado)
        : pos_x(x), pos_y(y), tipo(tipo), estado(estado) {}
};

//Clase que contiene la info de los objetos recolectables (monedas, zanahorias, etc)
class InfoRecolectable {
public:
    TipoRecolectable tipo;
    int pos_x;
    int pos_y;

    InfoRecolectable(TipoRecolectable tipo,  int x, int y) : 
                tipo(tipo), pos_x(x), pos_y(y) {}
};

class InfoProyectil {
public:
    int pos_x;
    int pos_y;
    Direcciones direccion;

    InfoProyectil(int x, int y, Direcciones dir) : 
                pos_x(x), pos_y(y), direccion(dir) {}
};
// Clase que representa la información del juego
class InfoJuego {
public:
    std::vector<InfoPlayer> players;
    std::vector<InfoEnemigo> enemigos;
    std::vector<InfoRecolectable> recolectables;
    std::vector<InfoProyectil> proyectiles;

    // Constructores
    InfoJuego() {};

    InfoJuego(const std::vector<InfoPlayer>& players,
              const std::vector<InfoEnemigo>& enemigos,
              const std::vector<InfoRecolectable>& recolectables,
              const std::vector<InfoProyectil>& proyectiles)
        : players(players), enemigos(enemigos), recolectables(recolectables), proyectiles(proyectiles) {}

    InfoJuego(std::vector<InfoPlayer>&& players,
              std::vector<InfoEnemigo>&& enemigos,
              std::vector<InfoRecolectable>&& recolectables,
              std::vector<InfoProyectil>&& proyectiles)
        : players(std::move(players)), enemigos(std::move(enemigos)), recolectables(std::move(recolectables)), proyectiles(std::move(proyectiles)) {}
    
    int getLengthData() {
        return (
            players.size() * LENGTH_PLAYER_INFO + 
            enemigos.size() * LENGTH_ENEMY_INFO + 
            recolectables.size() * LENGTH_ITEMS_INFO +
            proyectiles.size() * LENGTH_PROYECTIL_INFO
        );
    }

};

#endif