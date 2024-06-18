#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "constantes.h"
#include "constantes_protocolo.h"
#include <cstdint>
#include <iomanip>


// Clase que  unicamente funciones para codificar y decodificar bytes
class Protocol
{
protected:
    // para abstraerse de usar bytes fuera del protocolo, los decodifico en tipos de datos equivalentes

    AccionesPlayer decodeAction(uint8_t byte);
    Direcciones decodeDireccion(uint8_t byte);
    TipoPlayer decodeTipoPlayer(uint8_t byte);
    EstadosPlayer decodeEstadoPlayer(uint8_t byte);
    TipoEnemy decodeTipoEnemy(uint8_t byte);
    EstadosEnemy decodeEstadoEnemy(uint8_t byte);
    TipoRecolectable decodeTipoRecolectable(uint8_t byte);
    TipoArma decodeTipoArma(uint8_t byte);

    /* Obtener un byte equivalente al valor de cada enum. (Ver constantes_protocolo.h y constantes.h)*/

    uint8_t encodeAccion(const AccionesPlayer &accion);
    uint8_t encodeDireccion(const Direcciones &direccion);
    uint8_t encodeTipoPlayer(const TipoPlayer &tipo);
    uint8_t encodeEstadoPlayer(const EstadosPlayer &estado);
    uint8_t encodeTipoEnemy(const TipoEnemy &enemigo);
    uint8_t encodeEstadoEnemy(const EstadosEnemy &estado);
    uint8_t encodeTipoRecolectable(const TipoRecolectable &tipo);
    uint8_t encodeTipoArma(const TipoArma &tipo);
    
};

#endif //PROTOCOL_H
