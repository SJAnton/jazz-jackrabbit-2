#include "client_receiver.h"
#include <atomic>



ClientReceiver::ClientReceiver(ClientProtocol &protocol, Queue<InfoJuego> &recv_queue): 
protocolo(protocol), queueReceptora(recv_queue){}
void ClientReceiver::run() {
    while (_keep_running) {
        InfoJuego infoJuego = protocolo.recibirInformacionDelServer(&was_closed);
        if (was_closed)
            return;
        queueReceptora.push(infoJuego);
    }
}