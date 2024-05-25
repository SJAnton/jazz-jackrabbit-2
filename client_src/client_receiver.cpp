#include "client_receiver.h"
#include <atomic>



ClientReceiver::ClientReceiver(ClientProtocol &protocol, Queue<InfoJuego> &recv_queue): 
protocolo(protocol), queueReceptora(recv_queue){}

void ClientReceiver::run() {
    while (_keep_running) {
        if (was_closed)
            return;
        //uint8_t data = protocolo.recv_action(wc);

        //hacer:
        //InfoJuego infoJuego = protocolo.recibirInfoJuego(wc);     (no esta implementada todavia)
        //EstadosPlayer estado = infojuego.estado_clientPlayer;
        //queueReceptora.push(estado);
    }
}