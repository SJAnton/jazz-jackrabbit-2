#ifndef SERVER_GAMELOOP_H_
#define SERVER_GAMELOOP_H_

#include "server_game.h"
#include "server_queue.h"
#include "server_thread.h"
#include "server_queue_list.h"

class ServerGameloop : public Thread {
    private:
        Game game;

        std::shared_ptr<Queue<uint8_t>> &recv_q;

        std::shared_ptr<ServerQueueList> &sndr_qs;

        bool wc;

    public:
        ServerGameloop(std::shared_ptr<Queue<uint8_t>> recv_q,
                        std::shared_ptr<ServerQueueList> sndr_qs) :
                            recv_q(recv_q), sndr_qs(sndr_qs) {};

        void run() override;

        bool is_dead();

        void kill();
};
#endif
