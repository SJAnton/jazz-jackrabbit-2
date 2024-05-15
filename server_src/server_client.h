#ifndef SERVER_CLIENT_H_
#define SERVER_CLIENT_H_

#include <atomic>
#include <utility>

#include "common_socket.h"
#include "server_queue.h"
#include "server_thread.h"
#include "server_sender.h"
#include "server_receiver.h"
#include "server_queue_list.h"
#include "characters/server_character.h"

class Client : public Thread {
    private:    
        Socket sk;

        Character pl;

        int &id;

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
        Client(Socket socket, Character player, int &client_id, Queue<uint8_t> &recv_queue,
                ServerQueueList &sndr_queue_list) : sk(std::move(socket)),
                    pl(std::move(player)), id(client_id), q(recv_queue), sql(sndr_queue_list),
                        pr(sk), recv(pr, q, wc, is_alive), sndr(pr, sndr_queue, wc) {}

        void run() override;

        bool is_dead();

        void kill();
};
#endif
