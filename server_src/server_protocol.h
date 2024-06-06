#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <arpa/inet.h>
#include <string>
#include <vector>

#include "server_queue_list.h"
#include "../common_src/socket.h"
#include "../common_src/info_juego.h"

class ServerProtocol {
    private:
        Socket &sk;
        
    public:
        explicit ServerProtocol(Socket &socket) : sk(socket) {}

        std::vector<uint8_t> recv_init_msg(bool &was_closed);

        void send_id(uint8_t id, bool &was_closed);

        std::vector<uint8_t> recv_msg(bool &was_closed);

        void send_msg(std::vector<uint8_t> &msg, bool &was_closed);

        void send_game_data(QueueData &game_data, bool &was_closed);

        int disconnect();

    private:
        AccionesPlayer decodeAction(uint8_t byte);
        Direcciones decodeDireccion(uint8_t byte);

        uint8_t encodeEstadoPlayer(EstadosPlayer estado);
        uint8_t encodeTipoEnemy(TipoEnemy enemigo);
        uint8_t encodeEstadoEnemy(EstadosEnemy estado);
        uint8_t encodeTipoRecolectable(TipoRecolectable tipo);
        uint8_t encodeDireccion(Direcciones direccion);

        std::vector<uint8_t> encodeInfoJuego(const InfoJuego &info); //

        std::vector<uint8_t> encodePlayer(const InfoPlayer &InfoPlayer);
        std::vector<uint8_t> encodeEnemy(const InfoEnemigo &);
        std::vector<uint8_t> encodeRecolectable(const InfoRecolectable &);
        std::vector<uint8_t> encodeProyectil(const InfoProyectil &);
};
#endif  // SERVER_PROTOCOL_H_
