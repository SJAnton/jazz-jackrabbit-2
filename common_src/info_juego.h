#ifndef INFO_JUEGO_H
#define INFO_JUEGO_H

#include "constantes.h"
#include "constantes_protocolo.h"

#include <vector>
#include <cstdint>

#define LENGTH_PLAYER_INFO 10
#define LENGTH_ENEMY_INFO 6
#define LENGTH_ITEMS_INFO 5
#define LENGTH_PROYECTIL_INFO 5

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
    int municion;

    InfoPlayer(){};
    InfoPlayer(int id, int x, int y, EstadosPlayer e, int vida, int pts, TipoArma arma, int municion)
        : id(id), pos_x(x), pos_y(y), estado(e), vida(vida), puntos(pts), arma(arma), municion(municion){}
    InfoPlayer(const InfoPlayer& other) 
        : id(other.id), pos_x(other.pos_x), pos_y(other.pos_y), estado(other.estado), 
          vida(other.vida), puntos(other.puntos), arma(other.arma), municion(other.municion) {}

    
};


class InfoEnemigo {
public:
    TipoEnemy tipo;
    int pos_x;
    int pos_y;
    EstadosEnemy estado;

    InfoEnemigo(TipoEnemy tipo, int x, int y,  EstadosEnemy estado)
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

    InfoProyectil(int x, int y, const Direcciones &dir) : 
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
        : players(players), recolectables(recolectables), enemigos(enemigos), proyectiles(proyectiles) {}

    InfoJuego(std::vector<InfoPlayer>&& players,
              std::vector<InfoEnemigo>&& enemigos,
              std::vector<InfoRecolectable>&& recolectables,
              std::vector<InfoProyectil>&& proyectiles)
        : players(std::move(players)), recolectables(std::move(recolectables)), enemigos(std::move(enemigos)), proyectiles(std::move(proyectiles)) {}
    
    int getLengthData() const{
        return ( 4 +
            players.size() * LENGTH_PLAYER_INFO + 
            enemigos.size() * LENGTH_ENEMY_INFO + 
            recolectables.size() * LENGTH_ITEMS_INFO +
            proyectiles.size() * LENGTH_PROYECTIL_INFO
        );
    }
    int cantidadPlayers() const;
    int cantEnemigos() const;
    int cantRecolectables() const;
    int cantProyectiles() const;

    void addPlayer();

};

#endif
