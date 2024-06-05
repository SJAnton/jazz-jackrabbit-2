#ifndef SERVER_CLIENT_H_
#define SERVER_CLIENT_H_

#include <map>

#include "server_queue.h"
#include "server_thread.h"
#include "server_sender.h"
#include "server_receiver.h"
#include "server_queue_list.h"
#include "server_gameloop_list.h"
#include "../common_src/socket.h"
#include "../common_src/liberror.h"
#include "../common_src/info_juego.h"
#include "characters/server_player_jazz.h"
#include "characters/server_player_lori.h"
#include "characters/server_player_spaz.h"

using namespace std;

class Client : public Thread {
    private:    
        // ESTA DATA LA RECIBIMOS POR PARAMETRO EN EL CONSTRUCTOR
        Socket sk;
        
        int id;

        int gmlp_id_copy;

        atomic<int> &gmlp_id;

        GameloopList &gameloops;

        map<uint8_t, shared_ptr<CharacterMap>> &ch_maps;

        map<uint8_t, shared_ptr<ServerQueueList>> &monitors;

        map<uint8_t, shared_ptr<Queue<uint8_t>>> &gameloops_q;

        map<string, vector<uint8_t>> &data;

        ServerProtocol protocol;

        // ESTA DATA LA CREAMOS EN EL CONSTRUCTOR
        Queue<InfoJuego> sndr_q;

        shared_ptr<CharacterMap> ch_map;

        shared_ptr<Queue<uint8_t>> recv_q;

        shared_ptr<ServerQueueList> monitor;

        shared_ptr<Character> player;

        ServerReceiver recv;

        ServerSender sndr;

        bool wc = false;

        bool gmlp_wc = false;

        void reap_dead_gameloops();

        vector<uint8_t> get_games();

        void select_game(uint8_t game);

        void select_character(uint8_t character, uint8_t game);

    public:
        Client(Socket socket, int id, atomic<int> &gmlp_id, GameloopList &gameloops,
                map<uint8_t, shared_ptr<CharacterMap>> &ch_maps,
                    map<uint8_t, shared_ptr<ServerQueueList>> &monitors,
                        map<uint8_t, shared_ptr<Queue<uint8_t>>> &gameloops_q,
                            map<string, vector<uint8_t>> &data) :
                            sk(move(socket)), id(id), gmlp_id(gmlp_id), gameloops(gameloops),
                                ch_maps(ch_maps), monitors(monitors), gameloops_q(gameloops_q),
                                    data(data), protocol(sk), recv(protocol, recv_q, wc),
                                        sndr(protocol, sndr_q, wc) {}

        void run() override;

        bool is_dead();

        void kill();
};
#endif
