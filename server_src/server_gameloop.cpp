#include <chrono>
#include <thread>

#include "server_gameloop.h"

#define MILLISECONDS_PER_ITR 1000/15

void ServerGameloop::run() {
    auto expected_itr_time = std::chrono::milliseconds(MILLISECONDS_PER_ITR);
    while (!wc) {
        auto start_time = std::chrono::steady_clock::now();

        std::vector<uint8_t> actions = game.get_actions(recv_q);
        game.execute_actions(actions, character_map);
        
        game.tick();

        InfoJuego game_data = game.snapshot(character_map);
        game.send_snapshot(game_data, sndr_qs);

        auto end_time = std::chrono::steady_clock::now();
        auto itr_time = end_time - start_time;
        if (itr_time < expected_itr_time) {
            std::this_thread::sleep_for(expected_itr_time - itr_time);
        }
    }
}

bool ServerGameloop::is_dead() {
    return wc;
}

void ServerGameloop::kill() {
    wc = true;
    if (recv_q != nullptr) {
        recv_q->close();
    }
    monitors.erase(id);
    gameloops_q.erase(id);
}
