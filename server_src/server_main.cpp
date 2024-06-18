#include <fstream>

#include "server_acceptor.h"
#include "game/gameloop.h"
#include "game/game.h"

#include "server_queue_list.h"
#include "server_config_reader.h"

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
    ServerConfigReader reader(file);
    std::map<std::string, std::vector<uint8_t>> data = reader.read();
    Game::init();
    ServerAcceptor acceptor(SERVICENAME);
   
    acceptor.start();

    while (std::cin.get() != EXIT) {

    }
    acceptor.join();
    return SUCCESS;
}
