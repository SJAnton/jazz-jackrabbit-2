#include "client_receiver.h"
#include <atomic>

ClientReceiver::ClientReceiver(ClientProtocol &protocol, Queue<EstadosPlayer> &recv_queue, bool &was_closed): 
protocolo(protocol), queueReceptora(recv_queue), wc(was_closed){}

void ClientReceiver::run() {
    while (!wc) {
        //uint8_t data = protocolo.recv_action(wc);

        //hacer:
        //InfoJuego infoJuego = protocolo.recibirInfoJuego(wc);     (no esta implementada todavia)
        //EstadosPlayer estado = infojuego.estado_clientPlayer;
        //queueReceptora.push(estado);
    }
}