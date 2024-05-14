#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <arpa/inet.h>
#include <string>
#include <vector>

#include "common_socket.h"

class ServerProtocol {
    private:
        Socket &sk;
        
    public:
        explicit ServerProtocol(Socket &socket) : sk(socket) {}

        std::vector<uint8_t> recv_init_info();

        /* Recibe una acción mediante el socket */
        uint8_t recv_action(bool &was_closed);

        /* Envía el byte inicial, la cantidad de enemigos vivos y muertos, 
        *  y el evento (si un enemigo murió o revivió) */
        void send_msg(uint8_t &enemies_current, uint8_t &enemies_last, bool &was_closed);

        /* Cierra el socket pasado por parámetro */
        int disconnect();
};
#endif  // SERVER_PROTOCOL_H_
