#ifndef CLIENT_RECEIVER_H_
#define CLIENT_RECEIVER_H_

#include "../common_src/socket.h"
#include "../common_src/queue.h"
#include "client_protocol.h"
#include "../common_src/thread.h"
#include "../common_src/constantes.h"
#include <atomic>


class ClientReceiver : public Thread {
    private:
        ClientProtocol& protocolo;
        Queue<EstadosPlayer>& queueReceptora;
        bool& wc;
        //std::atomic<bool>& alive;

    public:
        ClientReceiver(ClientProtocol& protocol, Queue<EstadosPlayer>& recv_queue, bool &was_closed);

        virtual void run() override;
};

#endif
