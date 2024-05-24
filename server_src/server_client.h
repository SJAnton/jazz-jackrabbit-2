#ifndef SERVER_CLIENT_H_
#define SERVER_CLIENT_H_

#include <atomic>
#include <utility>

#include "server_queue.h"
#include "server_thread.h"
#include "server_sender.h"
#include "server_receiver.h"
#include "server_queue_list.h"
#include "../../common_src/socket.h"
#include "../../common_src/liberror.h"

#define MAX_ENEMIES 5

class Client : public Thread {
    private:    
        Socket sk;

        Queue<uint8_t> &q;

        ServerQueueList &sql;

        ServerProtocol pr;

        Queue<uint8_t> sndr_queue;

        std::atomic<bool> is_alive = true;

        std::atomic<bool> keep_running = true;

        bool wc = false;

        ServerReceiver recv;
        
        ServerSender sndr;

    public:
        Client(Socket socket, Queue<uint8_t> &recv_queue, ServerQueueList &sndr_queue_list) :
                sk(std::move(socket)), q(recv_queue), sql(sndr_queue_list), pr(sk),
                sndr_queue(MAX_ENEMIES * 2), recv(pr, q, wc, is_alive), sndr(pr, sndr_queue, wc) {}

        void run() override;

        bool is_dead();

        void kill();
};
#endif
