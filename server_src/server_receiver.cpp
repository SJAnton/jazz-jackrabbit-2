#include "server_receiver.h"

#define EXIT 0xFF

void ServerReceiver::run() {
    while (!was_closed) {
        //bool local_wc = was_closed.load();
        std::vector<uint8_t> data = pr.recv_msg(was_closed);
        //std::cout << "recibi un mensaje" <<std::endl;
        for (uint8_t action : data) {
            q->push(action);
            if (action == EXIT) {
                was_closed = true;
            }
        }
    }
}
