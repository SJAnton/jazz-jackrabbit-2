#ifndef SERVER_GAMELOOP_H_
#define SERVER_GAMELOOP_H_

#include "server_game.h"
#include "server_queue.h"
#include "server_thread.h"
#include "server_queue_list.h"
#include "map/server_game_map.h"
#include "server_character_map.h"
#include "objects/server_object.h"
#include "characters/server_enemy.h"

#define ITR_PER_SEC 15

class ServerGameloop : public Thread {
    private:
        Game game;

        ServerGameMap* gameMap;

        std::shared_ptr<CharacterMap> &character_map;

        std::shared_ptr<Queue<uint8_t>> &recv_q;

        std::shared_ptr<ServerQueueList> &sndr_qs;

        std::map<uint8_t, std::shared_ptr<ServerQueueList>> &monitors;

        std::map<uint8_t, std::shared_ptr<Queue<uint8_t>>> &gameloops_q;

        std::map<std::string, std::vector<uint8_t>> &data_map;

        std::list<std::shared_ptr<Projectile>> projectile_list;

        std::list<std::shared_ptr<Enemy>> enemy_list;

        std::list<std::shared_ptr<Object>> object_list;

        std::vector<std::shared_ptr<Character>> top_players;

        int time_left;

        int id;

        bool wc = false;

    public:
        ServerGameloop(std::shared_ptr<CharacterMap> &map,
                        std::shared_ptr<Queue<uint8_t>> &recv_q,
                         std::shared_ptr<ServerQueueList> &sndr_qs,
                          std::map<uint8_t, std::shared_ptr<ServerQueueList>> &monitors,
                            std::map<uint8_t, std::shared_ptr<Queue<uint8_t>>> &gameloops_q,
                             std::map<std::string, std::vector<uint8_t>> &data_map, int game_length,
                                int id) : character_map(map), recv_q(recv_q), sndr_qs(sndr_qs),
                                    monitors(monitors), gameloops_q(gameloops_q), data_map(data_map),
                                        time_left(game_length * ITR_PER_SEC), id(id) {};

        void run() override;

        bool is_dead();

        void kill();

        /*void setGameMap(ServerGameMap *game);

        bool is_id(int other_id);

        void send_map(Queue<InfoMap>* sndr_q);*/
};
#endif
