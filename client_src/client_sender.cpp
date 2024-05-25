#include "client_sender.h"
#include <atomic>

#include <iostream>

#define ATTACK 0x03

ClientSender::ClientSender(ClientProtocol &protocol, Queue<ComandoCliente> &send_queue): 
protocolo(protocol), queueEnviadora(send_queue){}

void ClientSender::run() {
    while (_keep_running) {
		if (was_closed)
			return;
    	ComandoCliente comando;
    	if(queueEnviadora.try_pop(comando)){
        	//protocolo.send_action(action, wc);
			std::cout <<"ComandoEnviado:" << comando.accion <<std::endl;

    	}
    }
}