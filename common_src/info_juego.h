#ifndef INFO_JUEGO_H
#define INFO_JUEGO_H

#include "constantes.h"

class InfoPlayer {
public:
    Position pos;
    EstadosPlayer estado;
    int vida;
    int puntos;
};

class InfoMoneda {
    Position pos;
    bool recolectada;
};

class InfoJuego {
public:
    InfoPlayer player1;
    InfoJuego() {}
    InfoJuego(InfoPlayer &player1) {
        this->player1 = player1;
    }
    InfoJuego(InfoPlayer &&player1) {
        this->player1 = player1;
    }

};

#endif
