#ifndef SERVER_CLIENT_H_
#define SERVER_CLIENT_H_

#include <map>

#include "server_sender.h"
#include "server_receiver.h"
#include "server_queue_list.h"
#include "server_gameloop_list.h"
#include "game/Map/game_map_reader.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "../common_src/socket.h"
#include "../common_src/liberror.h"
#include "../common_src/info_juego.h"

using namespace std;

class Client : public Thread {
    private:    
        Socket sk;

        int id;

        int game_time;

        atomic<int> &gmlp_id;

        GameloopList &gameloops;

        GameMapReader &map_reader;

        ServerGameloop *gameLoop;

        ServerProtocol protocol;

        Queue<InfoJuego> sndr_q;

        shared_ptr<Queue<uint8_t>> recv_q;

        std::unique_ptr<ServerReceiver> receiver;

        ServerSender sender;

        bool wc = false;

        bool is_running = false;

        void reap_dead_gameloops();

        vector<uint8_t> get_games();

        void select_game(uint8_t game, const TipoPlayer &type_player, Level &level);

        TipoPlayer select_character(uint8_t character);

    public:
        Client(Socket &&sk, int id, int game_time, atomic<int> &gmlp_id,
                GameloopList &gameloops, GameMapReader &map_reader);
        
        void run() override;

        bool is_dead();

        void kill();
};
#endif
