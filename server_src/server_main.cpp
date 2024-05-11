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
    Queue<uint8_t> recv_queue;
    ServerQueueList sndr_queue_list;
    // Lee la configuración de un archivo YAML y modifica el juego
    ServerConfigReader reader(/*archivo*/);

    bool was_closed = false;

    ServerAcceptor acceptor(skt, recv_queue, sndr_queue_list, was_closed);
    ServerGameloop gameloop(recv_queue, sndr_queue_list, was_closed);

    acceptor.start();
    gameloop.start();

    while (std::cin.get() != EXIT) {

    }
    was_closed = true;
    skt.shutdown(SHUTCODE);
    skt.close();
    recv_queue.close();
    acceptor.join();
    gameloop.join();
    return SUCCESS;
}
