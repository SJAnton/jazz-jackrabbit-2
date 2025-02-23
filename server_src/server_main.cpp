#include <fstream>

#include "game/game.h"
#include "game/gameloop.h"
#include "server_acceptor.h"
#include "server_queue_list.h"
#include "server_config_reader.h"
#include "../common_src/socket.h"
#include "game/Map/game_map_reader.h"

//#define GAME_KEY "Game"

#define CONFIG "config.yaml"

#define EXIT 'q'

#define SUCCESS 0
#define ERROR 1
#define SHUTCODE 2

#define SERVICENAME argv[1]

int main(int argc, char* argv[]) {
    if (SERVICENAME == nullptr) {
        throw std::invalid_argument("No servicename found");
        return ERROR;
    }
    std::ifstream file(CONFIG);
    if (!file.is_open()) {
        throw std::runtime_error("Failure opening configuration file");
    }
    Socket skt(SERVICENAME);
    bool was_closed = false;

    ServerConfigReader reader(file);
    std::map<std::string, std::vector<int>> data = reader.read();
    GameMapReader map_reader(data);

    Game::init(data);

    //ServerAcceptor acceptor(skt, data[GAME_KEY][0], map_reader, was_closed);
    ServerAcceptor acceptor(skt, map_reader, was_closed);
    acceptor.start();

    while (std::cin.get() != EXIT) {

    }
    was_closed = true;
    skt.shutdown(SHUTCODE);
    skt.close();
    acceptor.join();
    return SUCCESS;
}
