#ifndef SERVER_ACCEPTOR_H_
#define SERVER_ACCEPTOR_H_

#include <list>
#include <utility>

#include "server_app.h"
#include "server_thread.h"
#include "server_client.h"
#include "server_gameloop.h"
#include "server_queue_list.h"
#include "characters/server_player_jazz.h"
#include "characters/server_player_lori.h"
#include "characters/server_player_spaz.h"
#include "common_socket.h"
#include "common_liberror.h"

class ServerAcceptor : public Thread {
    private:
        Socket &sk;

        bool &wc;

        std::list<Client*> clients;

        std::list<ServerGameloop*> gameloops;

        std::vector<Queue<uint8_t>> rql;

        std::vector<ServerQueueList> sqll;

    public:
        ServerAcceptor(Socket &socket, bool &was_closed) : sk(socket), wc(was_closed) {}

        void run() override;

        void reap_dead();

        void kill_all();
};
#endif
