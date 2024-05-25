#ifndef SERVER_GAMELOOP_H_
#define SERVER_GAMELOOP_H_

#include "server_app.h"
#include "server_queue.h"
#include "server_thread.h"
#include "server_client.h"
#include "server_queue_list.h"
#include "../common_src/socket.h"

class ServerGameloop : public Thread {
    private:
        ServerApp srv;

        Queue<uint8_t> &q;

        ServerQueueList &sql;

        bool wc;

    public:
        ServerGameloop(Queue<uint8_t> &recv_queue, ServerQueueList &sndr_q_list) :
                        q(recv_queue), sql(sndr_q_list) {}

        void run() override;

        bool is_dead();

        void kill();
};
#endif
