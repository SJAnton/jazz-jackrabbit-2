#ifndef SERVER_ACCEPTOR_H_
#define SERVER_ACCEPTOR_H_

#include <map>
#include <list>
#include <utility>

#include "game/game.h"
#include "../common_src/thread.h"
#include "server_client.h"
#include "server_gameloop_list.h"
#include "server_queue_list.h"
#include "server_character_map.h"
//#include "characters/server_player_jazz.h"
//#include "characters/server_player_lori.h"
//#include "characters/server_player_spaz.h"
#include "../common_src/socket.h"
#include "../common_src/liberror.h"

using namespace std;

/**
 * Este hilo se ejecuta solo una vez y permanece abierto hasta que el server_main lo decida.
 * Se encarga de aceptar clientes, creando uno objeto Client por cada uno.
*/
class ServerAcceptor : public Thread {
    private:
        Socket sk; //server_sk
        bool was_closed;

        //atomic<int> gmlp_id = 1;

        list<Client> clients;

        GameloopList gameloops;

        //map<uint8_t, shared_ptr<Queue<uint8_t>>> gameloops_q;

        //map<uint8_t, shared_ptr<ServerQueueList>> monitors;

        //map<string, vector<uint8_t>> &data;

    public:
        ServerAcceptor(const std::string &hostname);

        void run() override;

        void reap_dead();

        void kill_all();
};
#endif
