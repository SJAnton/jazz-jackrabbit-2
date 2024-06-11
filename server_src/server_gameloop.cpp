#include <chrono>
#include <thread>

#include "server_gameloop.h"

#define PLAYER_ID_POS 0
#define EXIT_POS 1
#define EXIT_BYTE 0xFF

#define MILLISECONDS_PER_ITR 1000/15

void ServerGameloop::run() {
    auto expected_itr_time = std::chrono::milliseconds(MILLISECONDS_PER_ITR);
    while (!character_map->empty() && time_left > 0) {
        auto start_time = std::chrono::steady_clock::now();

        std::vector<uint8_t> actions = game.get_actions(recv_q);
        if (actions.size() > EXIT_POS && actions.at(EXIT_POS) == EXIT_BYTE) {
            uint8_t player_id = actions.at(PLAYER_ID_POS);
            game.remove_character(player_id, character_map);
            continue;
        }
        game.execute_actions(actions, character_map, projectile_list, data_map);

        game.tick(character_map, top_players, projectile_list, enemy_list, object_list);

        InfoJuego game_data = game.snapshot(character_map);
        game.send_snapshot(game_data, sndr_qs);

        auto end_time = std::chrono::steady_clock::now();
        auto itr_time = end_time - start_time;
        if (itr_time < expected_itr_time) {
            std::this_thread::sleep_for(expected_itr_time - itr_time);
        }
        time_left--; // TODO: enviar por InfoJuego
    }
    wc = true;
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
