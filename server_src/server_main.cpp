#include <fstream>

#include "server_acceptor.h"
#include "server_gameloop.h"
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
    Socket skt(SERVICENAME);
    ServerConfigReader reader(file);
    std::map<std::string, std::vector<uint8_t>> data = reader.read();

    bool was_closed = false;

    ServerAcceptor acceptor(skt, data, was_closed);

    acceptor.start();

    while (std::cin.get() != EXIT) {

    }
    was_closed = true;
    skt.shutdown(SHUTCODE);
    skt.close();
    acceptor.join();
    return SUCCESS;
}
