#include "client_sender.h"
#include <atomic>

#include <iostream>

ClientSender::ClientSender(ClientProtocol &protocol, Queue<ComandoCliente> &send_queue): 
protocolo(protocol), queueEnviadora(send_queue){}

void ClientSender::run() {
    while (_keep_running) {
		if (was_closed)
			return;
    	ComandoCliente comando;
    	if(queueEnviadora.try_pop(comando)){
			protocolo.enviarComandoAlServer(comando, &was_closed);
    	}
    }
}