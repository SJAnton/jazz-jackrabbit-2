#include "server_client.h"

#define GAME_POS 0
#define CHAR_POS 1

#define NEW_GAME 0x00

#define JAZZ_BYTE 0x01
#define LORI_BYTE 0x02
#define SPAZ_BYTE 0x03

#define SHUTCODE 2

Client::Client(Socket &&_sk, int id, int game_time, atomic<int> &gmlp_id,
                GameloopList &gameloops, GameMapReader &map_reader) :
                sk(std::move(_sk)), id(id), game_time(game_time), gmlp_id(gmlp_id),
                gameloops(gameloops), map_reader(map_reader), protocol(sk),
                recv_q(std::make_shared<Queue<uint8_t>>()), sender(protocol, sndr_q, wc) {}


void Client::run() {
    reap_dead_gameloops();

    vector<uint8_t> msg = get_games(); // Envía las partidas disponibles (TODO: enviar escenarios)
    std::map<uint8_t, Level> levels = map_reader.read_levels();

    Level demo_level = levels.at(0);

    protocol.send_msg(msg, wc);

    // Recibe partida y personaje (TODO: recibir escenario elegido)
    vector<uint8_t> init_data = protocol.recv_init_msg(wc);

    if (init_data[GAME_POS] != NEW_GAME && !gameloops.contains(init_data[GAME_POS])) {
        std::cout << "Entra al if" << std::endl;
        kill();
        throw runtime_error("Game not found");
    }
    TipoPlayer player_selected = select_character(init_data[1]);
    select_game(init_data[0], player_selected, demo_level);

    protocol.send_id(id, wc); // Envía al cliente su ID

    receiver->start();
    sender.start();

    is_running = true;
}

TipoPlayer Client::select_character(uint8_t type_player) {
     switch (type_player) {
        case JAZZ_BYTE:
            return TipoPlayer::Jazz;
        case LORI_BYTE:
            return TipoPlayer::Lori;
        case SPAZ_BYTE:
            return TipoPlayer::Spaz;
        default:
            kill();
            throw runtime_error("No character chosen");
    }
}

void Client::select_game(uint8_t game, const TipoPlayer &type_player, Level &level) {
    if (game == NEW_GAME) {
        // Creo un Nuevo Gameloop y el receiver utilizará la queue de aquí
        int id_game = gmlp_id++;

        //gameLoop = new ServerGameloop(id_game, id, game_time, type_player, recv_q, &sndr_q, level);
        gameLoop = new ServerGameloop(id_game, id, game_time, type_player, recv_q, &sndr_q);

        receiver = std::make_unique<ServerReceiver>(protocol, recv_q, wc);

        gameloops.push_back(gameLoop); // Agrego el nuevo gameloop a la lista
        gameLoop->start();
        std::cout << "Inició un nuevo gameloop" << std::endl;
    } else {
        // Me uno al gameloop recibido, y el receiver cargará en la queue de ese gameloop
        gameLoop = gameloops.at(game);
        if (gameLoop == NULL) {
            std::runtime_error("Game not found");
        }
        receiver = std::make_unique<ServerReceiver>(protocol, gameLoop->recv_q, wc);
        gameLoop->addPlayer(id, type_player, &sndr_q);
        //gameLoop->addPlayer(id, type_player, &sndr_q, Coordenada(level.spawn_x, level.spawn_y));
        std::cout << "Se unió el cliente "<< id << " al gameloop " << gameLoop->getId() << std::endl;
    }
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
            ++it;
        }
    }
}

vector<uint8_t> Client::get_games() {
    vector<uint8_t> msg;
    
    msg.push_back(gameloops.size()); // Cantidad de partidas
    for (auto &game : gameloops) {
        msg.push_back(game->id);
    }
    return msg;
}

bool Client::is_dead() {
    return wc;
}

void Client::kill() {
    sndr_q.close();
    sk.close();

    if (!is_running) {
        return;
    }
    sender.join();

    std::cout << "El sender se cerró. El cliente se desconecto" << std::endl;
    gameLoop->removePlayer(id);
    if (gameLoop->is_dead()) {
        gameloops.remove(gameLoop);
    }
    receiver->join();
    std::cout << "El receiver se cerró." << std::endl;
}
