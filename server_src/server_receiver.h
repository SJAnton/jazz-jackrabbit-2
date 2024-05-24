#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include "server_app.h"
#include "server_queue.h"
#include "server_thread.h"
#include "server_protocol.h"
#include "../../common_src/socket.h"

class ServerReceiver : public Thread {
    private:
        ServerProtocol &pr;

        Queue<uint8_t> &q;

        bool &wc;

        std::atomic<bool> &alive;

    public:
        ServerReceiver(ServerProtocol &protocol, Queue<uint8_t> &recv_queue,
                        bool &was_closed, std::atomic<bool> &is_alive) :
                            pr(protocol), q(recv_queue), wc(was_closed), alive(is_alive) {}

        void run() override;
};
#endif
