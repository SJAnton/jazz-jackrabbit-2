#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "server_protocol.h"
#include "../common_src/socket.h"

class ServerReceiver : public Thread {
    private:
        ServerProtocol &pr;

        std::shared_ptr<Queue<uint8_t>> &q;

        //std::atomic<bool> &wc;
        bool &was_closed;

    public:
        /*ServerReceiver(ServerProtocol &protocol, std::shared_ptr<Queue<uint8_t>> &recv_queue,
                        std::atomic<bool> &was_closed) : pr(protocol),
                            q(recv_queue), wc(was_closed) {}
        */
        ServerReceiver(ServerProtocol &protocol, std::shared_ptr<Queue<uint8_t>> &recv_queue,
                        bool &was_closed) : 
            pr(protocol), q(recv_queue), was_closed(was_closed) {}
        
        void run() override;
};
#endif
