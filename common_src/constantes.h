#ifndef CONSTANTES_H
#define CONSTANTES_H

//#include "info_juego.h"

#define ANCHO_WINDOW 750
#define ALTO_WINDOW 500 

enum class EstadosPlayer {Inactive, Walking, Running, Jumping, Falling, Shooting,
    SpecialAttack, IntoxicatedIdle, IntoxicatedWalk, Damaged, Dying, Dead, Reviving
};

enum TipoPlayer {Jazz, Spaz, Lori};

enum class AccionesPlayer{Idle, Walk, Run, Jump, Shoot, SpecialAttack};

enum class EstadosEnemy{Idle, Move, Attack, Damaged, Death};
enum TipoEnemy{Rat, Bat, Lizard};

enum TipoRecolectable {Moneda, Diamante, Zanahoria, Municion};

enum class TipoArma {Comun};

enum Direcciones {Left, Right};


enum TipoComando { AccionPlayer, MensajeInicial };

class ComandoCliente {
private:
    AccionesPlayer accion;
    Direcciones direccion;
    int id_partida;
    TipoPlayer tipoPlayer;
    TipoComando tipoComando;

public:
    ComandoCliente(AccionesPlayer accion, Direcciones direccion) 
        : accion(accion), direccion(direccion) {
        tipoComando = AccionPlayer;
    }

    ComandoCliente(int id_partida, TipoPlayer tipo) 
        : id_partida(id_partida), tipoPlayer(tipo) {
        tipoComando = MensajeInicial;
    }

    ComandoCliente() { }

    // Getters
    AccionesPlayer getAccion() const { return accion; }
    Direcciones getDireccion() const { return direccion; }
    int getIdPartida() const { return id_partida; }
    TipoPlayer getTipoPlayer() const { return tipoPlayer; }
    TipoComando getTipoComando() const { return tipoComando; }
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
