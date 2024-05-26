#include "server_receiver.h"

#define EXIT 0x00

void ServerReceiver::run() {
    while (!wc) {
        std::vector<uint8_t> data = pr.recv_msg(wc);
        for (uint8_t action : data) {
            if (action != EXIT) {
                q.push(action);
            }
            else {
                // Desconexión del cliente
                wc = true;
            }
        }
    }
}
