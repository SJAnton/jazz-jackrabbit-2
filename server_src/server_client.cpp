#include "server_client.h"

#define GAME_POS 0
#define CHAR_POS 1

#define NEW_GAME 0x00

#define JAZZ_BYTE 0x01
#define LORI_BYTE 0x02
#define SPAZ_BYTE 0x03

#define JAZZ_CODE "PlayerJazz"
#define LORI_CODE "PlayerLori"
#define SPAZ_CODE "PlayerSpaz"

#define INIT_POS 0

#define SHUTCODE 2

void Client::run() {
    reap_dead_gameloops();

    vector<uint8_t> msg = get_games();
    //msg.push_back(escenarios);

    protocol.send_msg(msg, wc);
    vector<uint8_t> init_data = protocol.recv_init_msg(wc);
    if (init_data[GAME_POS] != NEW_GAME && !gameloops_q.count(init_data[GAME_POS])) {
        kill();
        throw runtime_error("Game not found");
    }
    protocol.send_id(id, wc);

    select_character(init_data[CHAR_POS], init_data[GAME_POS]);
    select_game(init_data[GAME_POS]);
}

void Client::reap_dead_gameloops() {
    for (auto it = gameloops.begin(); it != gameloops.end();) {
        ServerGameloop *gameloop = *it;
        if (gameloop->is_dead()) {
            gameloop->kill();
            gameloop->join();
            it = gameloops.erase(it); // Devuelve la siguiente posición
            delete gameloop;
        } else {
            it++;
        }
    }
}

vector<uint8_t> Client::get_games() {
    vector<uint8_t> msg;
    msg.push_back(gameloops_q.size()); // Cantidad de partidas
    for (auto &key : gameloops_q) {
        msg.push_back(key.first);
    }
    return msg;
}

void Client::select_game(uint8_t game) {
    if (game == NEW_GAME) {
        // Se crea un nuevo juego, el nuevo gameloop recibe un monitor
        // y una cola única
        
        // No se pierden las referencias al salir de la función
        recv_q = std::make_shared<Queue<uint8_t>>();
        monitor = std::make_shared<ServerQueueList>();

        int current_gmlp_id = gmlp_id.load();

        ServerGameloop *gameloop = new ServerGameloop(ch_map, recv_q, monitor, monitors,
                                                        gameloops_q, data, current_gmlp_id);
        
        gameloops_q[current_gmlp_id] = recv_q;
        monitors[current_gmlp_id] = monitor;

        gameloop->start();
        gameloops.push_back(gameloop);
        gmlp_id++;
    } else {
        // La partida ya existe, la cola del receiver es la cola
        // única del gameloop y el monitor recibe la cola del sender
        recv_q = gameloops_q.at(game);
        monitor = monitors.at(game);
    }
    monitor->push_back(&sndr_q);
    recv.start();
    sndr.start();
}

void Client::select_character(uint8_t character, uint8_t game) {
    if (game == NEW_GAME) {
        ch_map = std::make_shared<CharacterMap>();
        ch_maps[gmlp_id] = ch_map;
    } else {
        ch_map = ch_maps.at(game);
    }
    switch (character) {
        case JAZZ_BYTE:
            // TODO: completar con las posiciones del spawn
            player = make_shared<PlayerJazz>(INIT_POS, INIT_POS, data);
            break;
        case LORI_BYTE:
            player = make_shared<PlayerLori>(INIT_POS, INIT_POS, data);
            break;
        case SPAZ_BYTE:
            player = make_shared<PlayerSpaz>(INIT_POS, INIT_POS, data);
            break;
        default:
            kill();
            throw runtime_error("No character chosen");
    }
    ch_map->push_back(id, player);
}

bool Client::is_dead() {
    return wc;
}

void Client::kill() {
    sndr_q.close();
    sk.close();
    if (recv_q != nullptr) {
        monitor->remove(&sndr_q);
        ch_map->erase(id);
        recv.join();
        sndr.join();
    }
}
