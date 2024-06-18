#ifndef INFO_JUEGO_H
#define INFO_JUEGO_H

#include "constantes.h"
#include "constantes_protocolo.h"

#include <vector>
#include <cstdint>

#define LENGTH_PLAYER_INFO 12
#define LENGTH_ENEMY_INFO 7
#define LENGTH_ITEMS_INFO 5
#define LENGTH_PROYECTIL_INFO 6

// Clase que representa la información de un jugador
class InfoPlayer {
public:
    int id;
    int pos_x; // 2 bytes
    int pos_y; // 2 bytes
    Direcciones direccion;
    TipoPlayer tipoPlayer;
    EstadosPlayer estado;
    int vida;
    int puntos; // 1 byte
    TipoArma arma;
    int municion;

    InfoPlayer(){};
    
    InfoPlayer(int id, int x, int y, const Direcciones &dir, const TipoPlayer &tipoPlayer, 
               const EstadosPlayer &e, int vida, int pts, const TipoArma &arma, int municion) : 
                id(id), pos_x(x), pos_y(y), direccion(dir), tipoPlayer(tipoPlayer), 
                estado(e), vida(vida), puntos(pts), arma(arma), municion(municion) {}
};


class InfoEnemigo {
public:
    TipoEnemy tipo;
    int pos_x;
    int pos_y;
    Direcciones direccion;
    EstadosEnemy estado;

    InfoEnemigo(TipoEnemy tipo, int x, int y, const Direcciones &dir,  EstadosEnemy estado)
        : tipo(tipo), pos_x(x), pos_y(y), direccion(dir), estado(estado) {}
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
    TipoArma tipo;
    int pos_x;
    int pos_y;
    Direcciones direccion;

    InfoProyectil(TipoArma tipo, int x, int y, const Direcciones &dir) : 
                tipo(tipo), pos_x(x), pos_y(y), direccion(dir) {}
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

    // Constructor parametrizado usando rvalue references
    InfoJuego(std::vector<InfoPlayer>&& players,
              std::vector<InfoEnemigo>&& enemigos,
              std::vector<InfoRecolectable>&& recolectables,
              std::vector<InfoProyectil>&& proyectiles)
        : players(std::move(players)), enemigos(std::move(enemigos)), 
          recolectables(std::move(recolectables)), proyectiles(std::move(proyectiles)) {}

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
