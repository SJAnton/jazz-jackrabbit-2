#ifndef INFO_JUEGO_H
#define INFO_JUEGO_H

#include "constantes.h"

class InfoPlayer {
public:
    Position pos;
    EstadosPlayer estadoAnterior;
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
    InfoJuego(InfoPlayer &&player1) {
            this->player1 = player1;

    }

};

#endif
