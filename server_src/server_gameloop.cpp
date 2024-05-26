#include <chrono>
#include <thread>

#include "server_gameloop.h"

void ServerGameloop::run() {
    while (sndr_qs->size() > 0) {
        std::vector<uint8_t> actions = game.get_actions(*recv_q.get());
        game.execute_actions(actions);
    }
    wc = true;
}

bool ServerGameloop::is_dead() {
    return wc;
}

void ServerGameloop::kill() {
    recv_q->close();
}
