#ifndef SERVER_GAMELOOP_H_
#define SERVER_GAMELOOP_H_

#include "server_game.h"
#include "server_queue.h"
#include "server_thread.h"
#include "server_queue_list.h"
#include "server_character_map.h"
#include "objects/server_object.h"

#define TOP_PL_NUMBER 3

class ServerGameloop : public Thread {
    private:
        Game game;

        std::shared_ptr<CharacterMap> &character_map;

        std::shared_ptr<Queue<uint8_t>> &recv_q;

        std::shared_ptr<ServerQueueList> &sndr_qs;

        std::map<uint8_t, std::shared_ptr<ServerQueueList>> &monitors;

        std::map<uint8_t, std::shared_ptr<Queue<uint8_t>>> &gameloops_q;

        std::map<std::string, std::vector<uint8_t>> &data_map;

        std::list<std::shared_ptr<Projectile>> projectile_list;

        std::list<std::shared_ptr<Object>> object_list;

        std::vector<uint8_t> top_three_players_id[TOP_PL_NUMBER];

        int id;

        int time_left; // TODO: implementar

        bool wc = false;

    public:
        ServerGameloop(std::shared_ptr<CharacterMap> &map,
                        std::shared_ptr<Queue<uint8_t>> &recv_q,
                         std::shared_ptr<ServerQueueList> &sndr_qs,
                          std::map<uint8_t, std::shared_ptr<ServerQueueList>> &monitors,
                            std::map<uint8_t, std::shared_ptr<Queue<uint8_t>>> &gameloops_q,
                             std::map<std::string, std::vector<uint8_t>> &data_map, int id,
                                int game_length) : character_map(map), recv_q(recv_q),
                                    sndr_qs(sndr_qs), monitors(monitors), gameloops_q(gameloops_q),
                                        data_map(data_map), id(id), time_left(game_length) {};

        void run() override;

        bool is_dead();

        void kill();
};
#endif
