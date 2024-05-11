#ifndef SERVER_ACCEPTOR_H_
#define SERVER_ACCEPTOR_H_

#include <list>
#include <utility>

#include "server_app.h"
#include "server_thread.h"
#include "server_client.h"
#include "server_player.h"
#include "server_queue_list.h"
#include "common_socket.h"
#include "common_liberror.h"

class ServerAcceptor : public Thread {
    private:
        Socket &sk;

        Queue<uint8_t> &q;

        ServerQueueList &sql;

        bool &wc;

        std::list<Client*> clients;

    public:
        ServerAcceptor(Socket &socket, Queue<uint8_t> &recv_queue,
                        ServerQueueList &sndr_queue_list, bool &was_closed) :
                            sk(socket), q(recv_queue), sql(sndr_queue_list), wc(was_closed) {}

        void run() override;

        void reap_dead();

        void kill_all();
};
#endif
