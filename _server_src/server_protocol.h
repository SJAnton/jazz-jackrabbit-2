#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H


#include <string>
#include <vector>
#include <arpa/inet.h>

#include "../common_src/constantes.h"
#include "../common_src/constantes_protocolo.h"
#include "../common_src/info_juego.h"

class ServerProtocol {


private:
    uint8_t encodeEstadoPlayer(EstadosPlayer estado);
    uint8_t encodeTipoEnemy(TipoEnemy enemigo);
    uint8_t encodeEstadoEnemy(EstadosEnemy estado);
    uint8_t encodeTipoRecolectable(TipoRecolectable tipo);
    uint8_t encodeDireccion(Direcciones direccion);

public:
    AccionesPlayer decodeAction(uint8_t byte);
    Direcciones decodeDireccion(uint8_t byte);

    

    std::vector<uint8_t> encodeInfoJuego(const InfoJuego &info);
    
    std::vector<uint8_t> encodePlayer(const InfoPlayer &InfoPlayer);
    std::vector<uint8_t> encodeEnemy(const InfoEnemigo &);
    std::vector<uint8_t> encodeRecolectable(const InfoRecolectable &);
    std::vector<uint8_t> encodeProyectil(const InfoProyectil &);



};

#endif
