#include <chrono>
#include <thread>

#include "server_gameloop.h"

void ServerGameloop::run() {
    while (!wc && !character_map->empty()) {
        std::vector<uint8_t> actions = game.get_actions(recv_q);
        game.execute_actions(actions, character_map);
    }
    wc = true;
}

bool ServerGameloop::is_dead() {
    return wc;
}

void ServerGameloop::kill() {
    wc = true;
    recv_q->close();
    monitors.erase(id);
    gameloops_q.erase(id);
}
