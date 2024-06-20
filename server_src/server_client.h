#ifndef SERVER_CLIENT_H_
#define SERVER_CLIENT_H_

#include <map>

#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "server_sender.h"
#include "server_receiver.h"
#include "server_queue_list.h"
#include "server_gameloop_list.h"
#include "../common_src/socket.h"
#include "../common_src/liberror.h"
#include "../common_src/info_juego.h"
//#include "characters/server_player_jazz.h"
//#include "characters/server_player_lori.h"
//#include "characters/server_player_spaz.h"

using namespace std;

class Client : public Thread {
    private:    
        // ESTA DATA LA RECIBIMOS POR PARAMETRO EN EL CONSTRUCTOR
        Socket sk;
        int id;
        GameloopList &gameloops; // Lista de gameloops disponibles para unirse

        // ESTA DATA LA CREAMOS EN EL CONSTRUCTOR
        ServerGameloop *gameLoop; // puntero al gameloop seleccionado


        //map<uint8_t, shared_ptr<Queue<uint8_t>>> &gameloops_recv_queues; //cada gameloop tiene una queue para recibir

        ServerProtocol protocol;

        Queue<InfoJuego> sndr_q;
        shared_ptr<Queue<uint8_t>> recv_q; // sera un puntero a la queue del gameloop

        //shared_ptr<ServerQueueList> monitor;
        ServerReceiver *receiver; // antes de crearlo debo saber que queue utilizará
        ServerSender sender;

        bool wc = false;

        void reap_dead_gameloops();

        vector<uint8_t> get_games();

        void select_game(uint8_t game, const TipoPlayer &type_player);

        TipoPlayer select_character(uint8_t character);
        
    public:
        Client(Socket &&sk, int id,  GameloopList &gameloops);
        
        void run() override;

        bool is_dead();

        void kill();
};
#endif
