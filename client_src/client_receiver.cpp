#include "client_receiver.h"
#include <atomic>



ClientReceiver::ClientReceiver(ClientProtocol &protocol, Queue<InfoJuego> &recv_queue): 
protocolo(protocol), queueReceptora(recv_queue){}
int i = 0;
void ClientReceiver::run() {
    while (_keep_running) {
        InfoJuego infoJuego = protocolo.recibirInformacionDelServer(&was_closed);
        infoJuego.player1.pos.x += i;
        i++;
        if (was_closed)
            return;
        queueReceptora.push(infoJuego);
    }
}