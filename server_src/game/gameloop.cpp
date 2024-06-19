#include <chrono>
#include <thread>

#include "gameloop.h"

#define PLAYER_ID_POS 0
#define EXIT_POS 1
#define EXIT_BYTE 0xFF

#define MILLISECONDS_PER_ITR 1000/15

ServerGameloop::ServerGameloop(int id_game, int id_client, TipoPlayer tipoPlayer, 
                               std::shared_ptr<Queue<uint8_t>> recv_q, 
                               Queue<InfoJuego> *sndr_q) :
    id(id_game),
    recv_q(recv_q)
{
    sndr_queues.push_back(sndr_q, id_client);
    game.add_player(tipoPlayer, id_client);  
}

void ServerGameloop::addPlayer(int id_client, TipoPlayer tipoPlayer, Queue<InfoJuego> *sndr_q) {
    sndr_queues.push_back(sndr_q, id_client);
    game.add_player(tipoPlayer, id_client);  
}

void ServerGameloop::removePlayer(int id) {
    game.remove_player(id);
    sndr_queues.remove(id);
    std::cout << "player y sender eliminados del gameloop" << std::endl;
    std::cout << "Aun quedan: " << sndr_queues.size() << std::endl;
}

void ServerGameloop::run() {
    auto expected_itr_time = std::chrono::milliseconds(MILLISECONDS_PER_ITR);
    while (sndr_queues.size() > 0) {
        auto start_time = std::chrono::steady_clock::now();
                
        std::vector<uint8_t> data;
        uint8_t byte;
        while (recv_q->try_pop(byte)) {
            data.push_back(byte);
        }

        if (data.size() > EXIT_POS && data.at(EXIT_POS) == EXIT_BYTE) {
            uint8_t player_id = data.at(PLAYER_ID_POS);
            game.remove_player(player_id);
            continue;
        }
        game.update();
        game.execute_actions(data);

        send_snapshot();

        auto end_time = std::chrono::steady_clock::now();
        auto itr_time = end_time - start_time;
        if (itr_time < expected_itr_time) {
            std::this_thread::sleep_for(expected_itr_time - itr_time);
        }
        //time_left--;
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
