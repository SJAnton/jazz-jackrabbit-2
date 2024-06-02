#ifndef SERVER_GAMELOOP_H_
#define SERVER_GAMELOOP_H_

#include "server_game.h"
#include "server_queue.h"
#include "server_thread.h"
#include "server_queue_list.h"
#include "server_character_map.h"

class ServerGameloop : public Thread {
    private:
        Game game;

        std::shared_ptr<CharacterMap> &character_map;

        std::shared_ptr<Queue<uint8_t>> &recv_q;

        std::shared_ptr<ServerQueueList> &sndr_qs;

        bool wc = false;

    public:
        ServerGameloop(std::shared_ptr<CharacterMap> &map,
                        std::shared_ptr<Queue<uint8_t>> &recv_q,
                            std::shared_ptr<ServerQueueList> &sndr_qs) :
                                character_map(map), recv_q(recv_q), sndr_qs(sndr_qs) {};

        void run() override;

        bool is_dead();

        void kill();
};
#endif
