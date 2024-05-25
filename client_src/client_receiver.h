#ifndef CLIENT_RECEIVER_H_
#define CLIENT_RECEIVER_H_

#include "../common_src/socket.h"
#include "../common_src/queue.h"
#include "client_protocol.h"
#include "../common_src/thread.h"
#include "../common_src/constantes.h"
#include "../common_src/info_juego.h"

#include <atomic>


class ClientReceiver : public Thread {
    private:
        ClientProtocol& protocolo;
        Queue<InfoJuego>& queueReceptora;
        bool was_closed = false;
        //std::atomic<bool>& alive;

    public:
        ClientReceiver(ClientProtocol& protocol, Queue<InfoJuego>& recv_queue);

        virtual void run() override;
};

#endif
