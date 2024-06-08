#include "client_receiver.h"
#include <atomic>



ClientReceiver::ClientReceiver(ClientProtocol &protocol, Queue<InfoJuego> &recv_queue): 
protocolo(protocol), queueReceptora(recv_queue), was_closed(false){}


void ClientReceiver::run() {
    int i = 0;
    while (_keep_running) {
        InfoJuego infoJuego = protocolo.recibirInformacion(&was_closed);
        if (infoJuego.players[0].estado == EstadosPlayer::Jumping && i ==0) {
             std::cout << "recibido saltando" << std::endl;
             i++;
        }
           
        if (was_closed)
            break;;
        queueReceptora.push(infoJuego);
    }
    std::cout << "me fui del receiver" << std::endl;
}
