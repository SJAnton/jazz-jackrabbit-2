#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H


#include <string>
#include <vector>
#include <arpa/inet.h>

#include "../common_src/constantes.h"
#include "../common_src/constantes_protocolo.h"

class ServerProtocol
{
private:
public:
    AccionesPlayer decodeAction(uint8_t byte) {
        switch (byte)
        {
        case ACTION_IDLE: return AccionesPlayer::Idle;
        case ACTION_WALK: return AccionesPlayer::Walk;
        case ACTION_RUN: return AccionesPlayer::Run;
        case ACTION_JUMP: return AccionesPlayer::Jump;
        case ACTION_SHOOT: return AccionesPlayer::Shoot;
        case ACTION_SPECIAL_ATACK: return AccionesPlayer::SpecialAttack;
        default:
            //Excepcion
            return AccionesPlayer::Idle;
        }
    }
    Direcciones decodeDireccion(uint8_t byte) {
        switch (byte)
        {
        case LEFT: return Direcciones::Left;
        case RIGHT: return Direcciones::Right;
        default:
            //Excepcion
            return Direcciones::Right;
        }
    }
    uint8_t codeEstado(EstadosPlayer estado) {
        switch (estado)
        {
        case Inactivo: return STATE_IDLE;
        case Caminando: return STATE_WALK;
        case Corriendo: return STATE_RUN;
        case Saltando: return STATE_JUMP;
        case Disparando: return STATE_SHOOT;
        case AtaqueEspecial: return STATE_SPECIAL_ATTACK;
        default: 
            return STATE_IDLE;
        }
    }
    
};

#endif
