#include "client_receiver.h"
#include <atomic>

ClientReceiver::ClientReceiver(ClientProtocol &protocol, Queue<uint8_t> &recv_queue, bool &was_closed): 
protocolo(protocol), queueReceptora(recv_queue), wc(was_closed){}

void ClientReceiver::run() {
    while (!wc) {
        uint8_t data = protocolo.recv_action(wc);
        queueReceptora.push(data);
    }
}