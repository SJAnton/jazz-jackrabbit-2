#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <arpa/inet.h>
#include <string>
#include <vector>

#include "../common_src/socket.h"

class ServerProtocol {
    private:
        Socket &sk;
        
    public:
        explicit ServerProtocol(Socket &socket) : sk(socket) {}

        std::vector<uint8_t> recv_init_msg(bool &was_closed);

        std::vector<uint8_t> recv_msg(bool &was_closed);

        void send_msg(std::vector<uint8_t> msg, bool &was_closed);

        /* Cierra el socket pasado por parámetro */
        int disconnect();
};
#endif  // SERVER_PROTOCOL_H_
