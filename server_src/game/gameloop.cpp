#include <chrono>
#include <thread>

#include "gameloop.h"

#define PLAYER_ID_POS 0
#define EXIT_POS 1
#define EXIT_BYTE 0xFF

#define ITR_PER_SEC 15
#define MILLISECONDS_PER_ITR 1000/15

ServerGameloop::ServerGameloop(int id_game, int id_client, int time_left, TipoPlayer tipoPlayer,
                               std::shared_ptr<Queue<uint8_t>> recv_q, Queue<InfoJuego> *sndr_q,
                               Level &level) : game(level), id(id_game),
                               time_left(time_left * ITR_PER_SEC), recv_q(recv_q) {    
    sndr_queues.push_back(sndr_q, id_client);
    game.add_player(tipoPlayer, id_client, Coordenada(level.spawn_x, level.spawn_y));  
}

void ServerGameloop::addPlayer(int id_client, TipoPlayer tipoPlayer, Queue<InfoJuego> *sndr_q,
                               Coordenada spawn) {
    sndr_queues.push_back(sndr_q, id_client);
    game.add_player(tipoPlayer, id_client, spawn);  
}

void ServerGameloop::removePlayer(int id) {
    game.remove_player(id);
    sndr_queues.remove(id);
    std::cout << "player y sender eliminados del gameloop" << std::endl;
    std::cout << "Aun quedan: " << sndr_queues.size() << std::endl;
    if (sndr_queues.size() == 0) {
        std::cout << "Terminar Gameloop" << std::endl;
        kill();
    }

}

void ServerGameloop::run() {
    auto expected_itr_time = std::chrono::milliseconds(MILLISECONDS_PER_ITR);
    while (sndr_queues.size() > 0 && time_left >= 0) {
        auto start_time = std::chrono::steady_clock::now();

        std::vector<uint8_t> data;
        uint8_t byte;
        while (recv_q->try_pop(byte)) {
            data.push_back(byte);
        }
        game.update();
        game.execute_actions(data);

        send_snapshot();

        auto end_time = std::chrono::steady_clock::now();
        auto itr_time = end_time - start_time;
        if (itr_time < expected_itr_time) {
            std::this_thread::sleep_for(expected_itr_time - itr_time);
        }
        time_left--;
    }
    std::cout << "fin gameloop" << std::endl;
    wc = true;
}

void ServerGameloop::send_snapshot() {
    InfoJuego game_data = game.snapshot();
    sndr_queues.push_to_all_queues(game_data);
}

bool ServerGameloop::is_dead() {
    return wc;
}

int ServerGameloop::getId() {
    return id;
}


void ServerGameloop::kill() {
    wc = true;
    if (recv_q != nullptr) {
        recv_q->close();
    }
    sndr_queues.clear();
}
