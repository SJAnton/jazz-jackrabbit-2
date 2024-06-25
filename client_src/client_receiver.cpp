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
    } catch (const ClosedQueue& e) { // si la queue fue cerrada
        std::cout << "la queueReceptora fue cerrada en el receiver" << std::endl;
        ClientPlayer::queueEnviadora.close();
        was_closed = true;
        stop();
    } catch (const std::exception& e) { // falló algo del socket
        std::cout << "el socket se cerró. En el receiver" << std::endl;
        std::cout << "Cierro la queueReceptora." << std::endl;
        queueReceptora.close();
        std::cout << "Cierro la queueEnviadora." << std::endl;
        ClientPlayer::queueEnviadora.close();
        
        //protocolo.close();
        was_closed = true;
        stop();

    } catch(...) {
        std::cerr << "Error INESPERADO en el Receiver: " << std::endl;
    }
    std::cout << "fin receiver" << std::endl;
}
