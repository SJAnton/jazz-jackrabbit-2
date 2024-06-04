#include "client_receiver.h"
#include <atomic>



ClientReceiver::ClientReceiver(ClientProtocol &protocol, Queue<InfoJuego> &recv_queue): 
protocolo(protocol), queueReceptora(recv_queue), was_closed(false){}


void ClientReceiver::run() {
    while (_keep_running) {
        InfoJuego infoJuego = protocolo.recibirInformacionDelServer(&was_closed);
        if (was_closed)
            break;;
        queueReceptora.push(infoJuego);
    }
    std::cout << "me fui del receiver" << std::endl;
}