#include "server_receiver.h"

#define ATTACK 0x03

void ServerReceiver::run() {
    while (!wc) {
        uint8_t action = pr.recv_action(wc);
        if (action == ATTACK) {
            q.push(action);
        } else {
            // Desconexión del cliente
            alive = false;
        }
    }
}
