#ifndef CLIENT_SENDER_H_
#define CLIENT_SENDER_H_

#include "../common_src/socket.h"
#include "../common_src/queue.h"
#include "client_protocol.h"
#include "../common_src/thread.h"
#include "../common_src/constantes.h"
#include <atomic>


class ClientSender : public Thread {
    private:
        ClientProtocol& protocolo;
        Queue<ComandoCliente>& queueEnviadora;
        bool was_closed;

    public:
        ClientSender(ClientProtocol& protocol, Queue<ComandoCliente>& send_queue);

        virtual void run() override;
};

#endif