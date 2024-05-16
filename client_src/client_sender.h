#ifndef CLIENT_SENDER_H_
#define CLIENT_SENDER_H_

#include "socket.h"
#include "queue.h"
#include "client_protocol.h"
#include "thread.h"
#include <atomic>


class ClientSender : public Thread {
    private:
        ClientProtocol& protocolo;
        Queue<uint8_t>& queueEnviadora;
        bool& wc;
        //std::atomic<bool>& alive;

    public:
        ClientSender(ClientProtocol& protocol, Queue<uint8_t>& send_queue, bool &was_closed);

        virtual void run() override;
};

#endif