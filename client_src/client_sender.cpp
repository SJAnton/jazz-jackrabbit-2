#include "client_sender.h"
#include <atomic>
#include <iostream>

ClientSender::ClientSender(ClientProtocol &protocol, Queue<ComandoCliente> &send_queue): 
protocolo(protocol), queueEnviadora(send_queue), was_closed(false){}

void ClientSender::run() {
    while (_keep_running) {

		if (was_closed)
			break;
    	ComandoCliente comando;
    	if(queueEnviadora.try_pop(comando)){
			protocolo.enviarComandoAlServer(comando, &was_closed);
    	}
    }
	std::cout << "me fui del sender..." << std::endl;
	protocolo.close();
}