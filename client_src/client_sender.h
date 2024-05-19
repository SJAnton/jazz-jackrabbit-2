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
        Queue<AccionesPlayer>& queueEnviadora;
        bool& wc;
        //std::atomic<bool>& alive;

    public:
        ClientSender(ClientProtocol& protocol, Queue<AccionesPlayer>& send_queue, bool &was_closed);

        virtual void run() override;
};

#endif