#include "client_sender.h"
#include <atomic>
#include <iostream>

ClientSender::ClientSender(ClientProtocol &protocol, Queue<ComandoCliente> &send_queue): 
protocolo(protocol), queueEnviadora(send_queue), was_closed(false){}

void ClientSender::run() {
	try {	
		while (_keep_running) {
			if (was_closed)
				break;
			
			ComandoCliente  comando; //= queueEnviadora.pop();
			if(queueEnviadora.try_pop(comando)){
				protocolo.enviarComando(comando, &was_closed);
			}
		}
		std::cout << "me fui del sender..." << std::endl;
		protocolo.close();
	} catch (const std::exception& e) {
        std::cerr << "Error en el Sender: " << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Error INESPERADO en el Sender: " << std::endl;
    }
}