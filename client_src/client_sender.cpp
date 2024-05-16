#include "client_sender.h"
#include <atomic>

#define ATTACK 0x03

ClientSender::ClientSender(ClientProtocol &protocol, Queue<uint8_t> &send_queue, bool &was_closed): 
protocolo(protocol), queueEnviadora(send_queue), wc(was_closed){}

void ClientSender::run() {
    while (!wc) {
    	uint8_t action;
    	if(queueEnviadora.try_pop(action)){
        	protocolo.send_action(action, wc);
    	}
    }
}