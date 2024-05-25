#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include "server_app.h"
#include "server_queue.h"
#include "server_thread.h"
#include "server_protocol.h"
#include "../common_src/socket.h"

class ServerReceiver : public Thread {
    private:
        ServerProtocol &pr;

        Queue<uint8_t> &q;

        bool &wc;

    public:
        ServerReceiver(ServerProtocol &protocol, std::shared_ptr<Queue<uint8_t>> recv_queue,
                        bool &was_closed) : pr(protocol), q(*recv_queue.get()), wc(was_closed) {}

        void run() override;
};
#endif
