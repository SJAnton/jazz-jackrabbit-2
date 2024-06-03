#ifndef CONSTANTES_H
#define CONSTANTES_H

//#include "info_juego.h"

enum class EstadosPlayer {Inactive, Walking, Running, Jumping, Falling, Shooting,
    SpecialAttack, IntoxicatedIdle, IntoxicatedWalk, Hit, Dying, Dead, Reviving
};

enum TipoPlayer {Jazz, Spaz, Lori};

enum class AccionesPlayer{Idle, Walk, Run, Jump, Shoot, SpecialAttack};

enum class EstadosEnemy{Idle, MoveLeft, MoveRight, Attack, Damaged, Death};
enum TipoEnemy{Rata, Bat};

enum TipoRecolectable {Moneda, Diamante, Zanahoria, Municion};

enum class TipoArma {Comun};

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
    Position() {}
    explicit Position(int x, int y) : x(x), y(y){
    }
    bool operator==(const Position& other) const {//capaz que sirve. Sino lo sacamos
        return (x == other.x && y == other.y);
    };
};




#endif
