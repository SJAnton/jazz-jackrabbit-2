#ifndef SERVER_ACCEPTOR_H_
#define SERVER_ACCEPTOR_H_

#include <map>
#include <list>
#include <utility>

#include "server_game.h"
#include "server_thread.h"
#include "server_client.h"
#include "server_gameloop_list.h"
#include "server_queue_list.h"
#include "server_character_map.h"
#include "characters/server_player_jazz.h"
#include "characters/server_player_lori.h"
#include "characters/server_player_spaz.h"
#include "../common_src/socket.h"
#include "../common_src/liberror.h"

using namespace std;

class ServerAcceptor : public Thread {
    private:
        Socket &sk;

        bool &srv_wc;

        atomic<int> gmlp_id = 1;

        list<Client*> clients;

        GameloopList gameloops;

        map<uint8_t, shared_ptr<CharacterMap>> ch_maps;

        map<uint8_t, shared_ptr<Queue<uint8_t>>> gameloops_q;

        map<uint8_t, shared_ptr<ServerQueueList>> monitors;

        map<string, vector<uint8_t>> &data;

    public:
        ServerAcceptor(Socket &socket, map<string, vector<uint8_t>> &obj_data,
                        bool &was_closed) : sk(socket), srv_wc(was_closed), data(obj_data) {}

        void run() override;

        void reap_dead();

        void kill_all();
};
#endif
