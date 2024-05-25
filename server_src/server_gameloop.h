#ifndef SERVER_GAMELOOP_H_
#define SERVER_GAMELOOP_H_

#include "server_app.h"
#include "server_queue.h"
#include "server_thread.h"
#include "server_queue_list.h"

class ServerGameloop : public Thread {
    private:
        ServerApp srv;

        Queue<uint8_t> &recv_q;

        ServerQueueList &sndr_qs;

        bool wc;

    public:
        ServerGameloop(Queue<uint8_t> &recv_queue, ServerQueueList &sndr_q_list) :
                        recv_q(recv_queue), sndr_qs(sndr_q_list) {}

        void run() override;

        bool is_dead();

        void kill();
};
#endif
