#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <arpa/inet.h>
#include <string>
#include <vector>

#include "../common_src/socket.h"
#include "../common_src/info_juego.h"
#include "../common_src/protocol.h"
#include "../common_src/tile_map.h"

class ServerProtocol : public Protocol{
    private:
        Socket &sk;
        
    public:
        explicit ServerProtocol(Socket &socket) : sk(socket) {}

        std::vector<uint8_t> recv_init_msg(bool &was_closed);

        void send_id(uint8_t id, bool &was_closed);

        std::vector<uint8_t> recv_msg(bool &was_closed);

        void send_msg(std::vector<uint8_t> &msg, bool &was_closed);

        void send_game_data(InfoJuego &game_data, bool &was_closed);

        void send_tile_map(TileMap &tile_map, bool &was_closed);

        int disconnect();

    private:
        void insertar2bytesDelNumero(int num, std::vector<uint8_t> &array);
        
        /** 
         * Crea el buffer con el mensaje para enviar al cliente.
         * Tiene la siguiente estructura:
         * 2 bytes con el size del mensaje +
         * 1 byte con la cantidad (n1) de players + {buffer player}*n1 + 
         * 1 byte con la cantidad (n2) de enemigos + {buffer enemy}*n2 +
         * 1 byte con la cantidad (n3) de recolectables + {buffer recolectables}*n3 +
         * 1 byte con la cantidad (n4) de proyectiles + {buffer proyectiles}*n4
         */
        std::vector<uint8_t> encodeInfoJuego(const InfoJuego &info);

        /**
         * Crea un buffer de 10 bytes con los datos un player, con la siguiente estructura:
         * [0] -> 1 byte con el id del cliente
         * [1] y [2] -> 2 bytes con la posicion de en x
         * [3] y [4] -> 2 bytes con la posicion de en y
         * [5] -> 1 byte con el estado de un player
         * [6] -> 1 byte con la vida
         * [7] -> 1 byte con los puntos
         * [8] -> 1 byte con el tipo de Arma
         * [9] -> 1 byte con las municiones
         */
        std::vector<uint8_t> encodePlayer(const InfoPlayer &InfoPlayer);

        /**
         * Crea un buffer de 6 bytes con los datos un enemigo, con la siguiente estructura:
         * [0] ->  1 byte con el tipo de Enemigo
         * [1] y [2] -> 2 bytes con la posicion de en x
         * [3] y [4] -> 2 bytes con la posicion de en y
         * [5] -> 1 byte con el estado del Enemigo
         */
        std::vector<uint8_t> encodeEnemy(const InfoEnemigo &);

        /**
         * Crea un buffer de 5 bytes con los datos un recolectable, con la siguiente estructura:
         * [0] ->  1 byte con el tipo de Recolectable
         * [1] y [2] -> 2 bytes con la posicion de en x
         * [3] y [4] -> 2 bytes con la posicion de en y
         */
        std::vector<uint8_t> encodeRecolectable(const InfoRecolectable &);

        /**
         * Crea un buffer de 5 bytes con los datos un proyectil, con la siguiente estructura:
         * [0] y [1] -> 2 bytes con la posicion de en x
         * [2] y [3] -> 2 bytes con la posicion de en y
         * [4] -> 1 byte con la direccion del proyectil
         */
        std::vector<uint8_t> encodeProyectil(const InfoProyectil &);

        /**
         * Crea un buffer de 2 + n*m bytes con la estructura de un mapa:
         * [0] -> 1 byte con cantidad de filas
         * [1] -> 1 byte con cantidad de columnas
         * n*m bytes con la matriz de tiles. Cada byte es un tipo de tile.
         * Envía el mapa por filas. Desde la 0 hasta la cantidad de filas.
         */
        std::vector<uint8_t> encodeTileMap(TileMap &tile_map);


};
#endif  // SERVER_PROTOCOL_H_
