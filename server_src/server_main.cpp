#include "server_acceptor.h"
#include "server_gameloop.h"
#include "server_queue_list.h"
#include "server_config_reader.h"

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
    Socket skt(SERVICENAME);
    // Lee la configuración de un archivo YAML y modifica el juego
    ServerConfigReader reader(/*settings.yaml*/);

    bool was_closed = false;

    ServerAcceptor acceptor(skt, was_closed);

    acceptor.start();

    while (std::cin.get() != EXIT) {

    }
    was_closed = true;
    skt.shutdown(SHUTCODE);
    skt.close();
    acceptor.join();
    return SUCCESS;
}
