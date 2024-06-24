#include "client_sender.h"
#include "client_player.h"
#include <atomic>
#include <iostream>

ClientSender::ClientSender(ClientProtocol &protocol, Queue<ComandoCliente> &send_queue): 
protocolo(protocol), queueEnviadora(send_queue), was_closed(false){}

void ClientSender::run() {
	try {	
		while (_keep_running) {
			if (was_closed)
				break;

			ComandoCliente  comando = queueEnviadora.pop();
			protocolo.enviarComando(comando, &was_closed);
		}
		protocolo.close();
	} catch (const ClosedQueue& e) { // si la queue fue cerrada, no se trata de un error
			was_closed = true;
			stop();
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
}