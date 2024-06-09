#include "client_receiver.h"
#include <atomic>



ClientReceiver::ClientReceiver(ClientProtocol &protocol, Queue<InfoJuego> &recv_queue): 
protocolo(protocol), queueReceptora(recv_queue), was_closed(false){}


void ClientReceiver::run() {
    try {
        while (_keep_running) {
        InfoJuego infoJuego = protocolo.recibirInformacion(&was_closed);
        if (was_closed)
            break;        
        queueReceptora.push(infoJuego);
        }
        std::cout << "me fui del receiver" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error en el Receiver: " << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Error INESPERADO en el Receiver: " << std::endl;
    }
    
}
