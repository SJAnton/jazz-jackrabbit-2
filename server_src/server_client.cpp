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

Client::Client(Socket &&_sk, int id,  GameloopList &gameloops) :
            sk(std::move(_sk)), id(id), gameloops(gameloops), protocol(sk), 
            recv_q(std::make_shared<Queue<uint8_t>>()),
            sender(protocol, sndr_q, wc)
{
    
}

TipoPlayer Client::select_character(uint8_t type_player) {
     switch (type_player)
        {
        case JAZZ_BYTE: return TipoPlayer::Jazz;
        case LORI_BYTE: return TipoPlayer::Lori;
        case SPAZ_BYTE: return TipoPlayer::Spaz;
        default:
            kill();
            throw runtime_error("No character chosen");
        }
}

void Client::select_game(uint8_t game, const TipoPlayer &type_player) {
    if (game == NEW_GAME) { // Creo un Nuevo Gameloop y el receiver utilizará la queue de aquí
        int id_game = gameloops.size() + 1; // para evitar el 0

        gameLoop = new ServerGameloop(id_game, id, type_player, recv_q, &sndr_q);
        receiver = new ServerReceiver(protocol, recv_q, wc);

        gameloops.push_back(gameLoop); // Agrego el nuevo gameloop a la lista
        gameLoop->start();
        std::cout << "Inició un nuevo gameloop" << std::endl;
    } 
    else { // Me uno al gameloop recibido, y el receiver cargará en la queue de ese gameloop
        gameLoop = gameloops.at(game);
        if (gameLoop == NULL) {
            std::runtime_error("Error. No se pudo encontrar la partida. En Client::select_game()");
        }

        recv_q = gameLoop->recv_q;
        receiver = new ServerReceiver(protocol, recv_q, wc);
        gameLoop->addPlayer(id, type_player, &sndr_q);
        std::cout << "Se unió el cliente "<< id << " al gameloop " << gameLoop->getId() << std::endl;
    }
}
void Client::run() {
    reap_dead_gameloops();
    //enviar ids de partidas
    vector<uint8_t> msg = get_games();
    protocol.send_msg(msg, wc);

    vector<uint8_t> init_data = protocol.recv_init_msg(wc); //recibo la eleccion de partida y personaje
    if (init_data[GAME_POS] != NEW_GAME && !gameloops.contains(init_data[GAME_POS])) {
        kill();
        throw runtime_error("Game not found");
    }
    TipoPlayer player_selected = select_character(init_data[1]);
    select_game(init_data[0], player_selected);

    protocol.send_id(id, wc); // Envio el id al cliente para que se lo guarde en el protocolo

    receiver->start();
    sender.start();

    sender.join();
    std::cout << "El sender se cerró. El cliente se desconecto" << std::endl;
    gameLoop->removePlayer(id);
    if (gameLoop->is_dead()) {
        gameloops.remove(gameLoop);
    }
    receiver->join();
    std::cout << "El receiver se cerró." << std::endl;


}

/**
 *  Recorre la lista de gameloops, eliminando y liberando la memoria de aquellos que han finalizado.
 */
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
    
   msg.push_back(gameloops.size()); // Cantidad de partidas
   for (auto game : gameloops) {
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
    if (recv_q != nullptr) {
        //monitor->remove(&sndr_q);
        //ch_map->erase(id);
        receiver->join();
        sender.join();
        delete receiver;
    }
}
