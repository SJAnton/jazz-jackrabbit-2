#include "server_receiver.h"

#define EXIT 0xFF

void ServerReceiver::run() {
    while (!wc) {
        bool local_wc = wc.load();
        std::vector<uint8_t> data = pr.recv_msg(local_wc);
        for (uint8_t action : data) {
            q->push(action);
            if (action == EXIT) {
                wc = true;
            }
        }
    }
}
