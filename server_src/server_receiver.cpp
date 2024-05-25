#include "server_receiver.h"

#define ATTACK 0x03

void ServerReceiver::run() {
    while (!wc) {
        std::vector<uint8_t> data = pr.recv_msg(wc);
        for (uint8_t action : data) {
            q->push(action);
            /*if (action == ATTACK) {
                // TODO: modificar
                q->push(action);
            } else {
                // Desconexión del cliente
                wc = true;
            }*/
        }
    }
}
