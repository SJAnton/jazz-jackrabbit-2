#ifndef CLIENT_RECEIVER_H_
#define CLIENT_RECEIVER_H_

#include "socket.h"
#include "queue.h"
#include "client_protocol.h"
#include "thread.h"
#include <atomic>


class ClientReceiver : public Thread {
    private:
        ClientProtocol& protocolo;
        Queue<uint8_t>& queueReceptora;
        bool& wc;
        //std::atomic<bool>& alive;

    public:
        ClientReceiver(ClientProtocol& protocol, Queue<uint8_t>& recv_queue, bool &was_closed);

        virtual void run() override;
};

#endif
