#ifndef SERVER_SENDER_H_
#define SERVER_SENDER_H_

#include "server_queue.h"
#include "server_thread.h"
#include "server_protocol.h"
#include "server_queue_list.h"
#include "../common_src/socket.h"

class ServerSender : public Thread {
    private:
        ServerProtocol &pr;

        Queue<QueueData> &q;

        bool &wc;

    public:
        ServerSender(ServerProtocol &protocol, Queue<QueueData> &queue, bool &was_closed) :
                        pr(protocol), q(queue), wc(was_closed) {}

        void run() override;
};
#endif
