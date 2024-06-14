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

        //std::shared_ptr<CharacterMap> &character_map;

        std::shared_ptr<Queue<uint8_t>> recv_q;

        ServerQueueList sndr_queues; //Lista de queues de los senders

       // std::map<uint8_t, std::shared_ptr<ServerQueueList>> &monitors;

        //std::map<uint8_t, std::shared_ptr<Queue<uint8_t>>> &gameloops_q;

        //std::map<std::string, std::vector<uint8_t>> &data_map;

        //std::list<std::shared_ptr<Projectile>> projectile_list;


        bool wc = false;

    public:
        ServerGameloop(int id_game, int id_client, TipoPlayer tipoPlayer, std::shared_ptr<Queue<uint8_t>> recv_q, 
                               Queue<InfoJuego> *sndr_q);

        void addPlayer(int id_client, TipoPlayer tipoPlayer, Queue<InfoJuego> *sndr_q);

        void send_snapshot();

        void run() override;

        bool is_dead();

        void kill();
};
#endif
