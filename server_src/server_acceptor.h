#ifndef SERVER_ACCEPTOR_H_
#define SERVER_ACCEPTOR_H_

#include <map>
#include <list>
#include <utility>

#include "server_app.h"
#include "server_thread.h"
#include "server_client.h"
#include "server_gameloop_list.h"
#include "server_queue_list.h"
#include "characters/server_player_jazz.h"
#include "characters/server_player_lori.h"
#include "characters/server_player_spaz.h"
#include "../common_src/socket.h"
#include "../common_src/liberror.h"

using namespace std;

class ServerAcceptor : public Thread {
    private:
        Socket &sk;

        bool &wc;

        ServerApp app;

        list<Client*> clients;

        GameloopList gameloops;

        map<uint8_t, shared_ptr<Queue<uint8_t>>> gameloops_q;

        map<uint8_t, shared_ptr<ServerQueueList>> monitors;

        map<string, vector<uint8_t>> &data;

    public:
        ServerAcceptor(Socket &socket, map<string, vector<uint8_t>> &obj_data,
                        bool &was_closed) : sk(socket), wc(was_closed), data(obj_data) {}

        void run() override;

        void reap_dead_clients();

        void reap_dead_gameloops();

        void kill_all();
};
#endif
