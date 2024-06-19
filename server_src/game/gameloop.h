#ifndef SERVER_GAMELOOP_H_
#define SERVER_GAMELOOP_H_

#include "game.h"
#include "../../common_src/queue.h"
#include "../../common_src/thread.h"
#include "../server_queue_list.h"
#include "../server_character_map.h"

#include "../../common_src/constantes.h"


class ServerGameloop : public Thread {
    public:
        Game game;

        int id;

        int time_left;

        std::shared_ptr<Queue<uint8_t>> recv_q;

        ServerQueueList sndr_queues; //Lista de queues de los senders

        bool wc = false;

    public:
        ServerGameloop(int id_game, int id_client, TipoPlayer tipoPlayer, std::shared_ptr<Queue<uint8_t>> recv_q, 
                               Queue<InfoJuego> *sndr_q);

        void addPlayer(int id_client, TipoPlayer tipoPlayer, Queue<InfoJuego> *sndr_q);
        void removePlayer(int id);
        void send_snapshot();

        void run() override;

        bool is_dead();

        int getId();

        void kill();
};
#endif
