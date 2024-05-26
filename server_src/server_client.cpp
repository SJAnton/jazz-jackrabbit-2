#include "server_client.h"

#define CHAR_BYTE 0x00
#define CHOSEN_GAME_BYTE 0x00
#define GAME_BYTE 0x00

#define NEW_GAME 0x00

#define JAZZ_BYTE 0x00
#define LORI_BYTE 0x01
#define SPAZ_BYTE 0x02

#define JAZZ_CODE "PlayerJazz"
#define LORI_CODE "PlayerLori"
#define SPAZ_CODE "PlayerSpaz"

#define SHUTCODE 2

void Client::run() {
    vector<uint8_t> msg;
    msg.push_back(gameloops.size());
    //msg.push_back(escenarios);

    protocol.send_msg(msg, wc);
    vector<uint8_t> init_data = protocol.recv_init_msg(wc);

    select_game(init_data[CHOSEN_GAME_BYTE], init_data[GAME_BYTE]);
    select_character(init_data[CHAR_BYTE]);
}

void Client::select_game(uint8_t game, uint8_t game_joined) {
    if (game == NEW_GAME) {
        // Se crea un nuevo juego, el nuevo gameloop recibe un monitor
        // y una cola única
        
        // No se pierden las referencias al salir de la función
        ch_map = std::make_shared<CharacterMap>();
        recv_q = std::make_shared<Queue<uint8_t>>();
        monitor = std::make_shared<ServerQueueList>();



        ServerGameloop *gameloop = new ServerGameloop(ch_map, recv_q, monitor);
        
        uint8_t id = gameloops_q.size();

        ch_maps.at(id) = ch_map;
        gameloops_q.at(id) = recv_q;
        monitors.at(id) = monitor;

        gameloop->start();
        gameloops.push_back(gameloop);
    } else {
        // La partida ya existe, la cola del receiver es la cola
        // única del gameloop y el monitor recibe la cola del sender
        ch_map = ch_maps.at(game_joined);
        recv_q = gameloops_q.at(game_joined);
        monitor = monitors.at(game_joined);
    }
    monitor->push_back(&sndr_q);
    recv.start();
    sndr.start();
}

void Client::select_character(uint8_t character) {
    switch (character) {
        case JAZZ_BYTE:
            player = make_unique<PlayerJazz>(data[JAZZ_CODE], id);
            break;
        case LORI_BYTE:
            player = make_unique<PlayerLori>(data[LORI_CODE], id);
            break;
        case SPAZ_BYTE:
            player = make_unique<PlayerSpaz>(data[SPAZ_CODE], id);
            break;
        default:
            throw runtime_error("No character chosen");
    }
    ch_map->at(id) = *player.get();
}

bool Client::is_dead() {
    return wc;
}

void Client::kill() {
    sndr_q.close();
    sk.close();
    if (recv_q != nullptr) {
        monitor->remove(&sndr_q);
        recv.join();
        sndr.join();
    }
}
