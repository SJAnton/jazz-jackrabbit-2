#include "client_receiver.h"
#include <atomic>

#include "client_player.h"


ClientReceiver::ClientReceiver(ClientProtocol &protocol, Queue<InfoJuego> &recv_queue, bool &wc): 
protocolo(protocol), queueReceptora(recv_queue), was_closed(wc){}


void ClientReceiver::run() {
    try {
        while (_keep_running) {
            InfoJuego infoJuego = protocolo.recibirInformacion(&was_closed);
            if (was_closed)
                break;        
            queueReceptora.push(infoJuego);
        }
        queueReceptora.close();
        ClientPlayer::queueEnviadora.close();
    } catch (const ClosedQueue& e) { // si la queue fue cerrada, no se trata de un error
        was_closed = true;
        stop();
    } catch (const std::exception& e) {
        queueReceptora.close();
        ClientPlayer::queueEnviadora.close();
        protocolo.close();
        was_closed = true;
        stop();
        std::cerr << "Error en el Receiver: " << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Error INESPERADO en el Receiver: " << std::endl;
    }
    std::cout << "fin receiver" << std::endl;
}
