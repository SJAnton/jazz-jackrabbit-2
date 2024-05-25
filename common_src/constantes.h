#ifndef CONSTANTES_H
#define CONSTANTES_H

//#include "info_juego.h"

enum EstadosPlayer {Inactivo, Caminando, Corriendo, Saltando, Cayendo, Disparando,
                    AtaqueEspecial, Intoxicado, Impacado, Muriendo, Muerto, Reviviendo};

enum AccionesPlayer{Idle, Walk, Run, Jump, Shoot, SpecialAttack};
enum EstadosEnemy{};
enum TipoPlayer {Jazz, Spaz, Lori};
enum Direcciones {Left, Right};

class ComandoCliente {
public:
    AccionesPlayer accion;
    Direcciones direccion;

    ComandoCliente(AccionesPlayer accion, Direcciones direccion){
        this->accion = accion;
        this->direccion = direccion;
    }
    ComandoCliente(){    }
};

class Position {
    public:
    int x = 0;
    int y = 0;
    bool operator==(const Position& other) const {//capaz que sirve. Sino lo sacamos
        return (x == other.x && y == other.y);
    };
};




#endif
