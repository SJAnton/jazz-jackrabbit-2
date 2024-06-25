#include "client_sender.h"
#include "client_player.h"
#include <atomic>
#include <iostream>

ClientSender::ClientSender(ClientProtocol &protocol, Queue<ComandoCliente> &send_queue, bool &wc): 
protocolo(protocol), queueEnviadora(send_queue), was_closed(wc){}

void ClientSender::run() {
	try {	
		while (_keep_running && !was_closed) {
			/*if (was_closed)
				break;*/
			ComandoCliente  comando = queueEnviadora.pop();
			protocolo.enviarComando(comando, &was_closed);
		}
		protocolo.close();
	} catch (const ClosedQueue& e) { // si la queue fue cerrada, no se trata de un error
		was_closed = true;
		//stop();
		protocolo.close();
	} catch (const std::exception& e) {
        std::cerr << "Error en el Sender: " << e.what() << std::endl;
		queueEnviadora.close();
		ClientPlayer::queueReceptora.close();
		protocolo.close();
		was_closed = true;
		stop();
    } catch(...) {
        std::cerr << "Error INESPERADO en el Sender: " << std::endl;
		queueEnviadora.close();
		protocolo.close();
		was_closed = true;
		stop();
    }
	std::cout << "fin sender" << std::endl;
}