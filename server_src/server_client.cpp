#include "server_client.h"

#include "../../common_src/liberror.h"

#define SHUTCODE 2

void Client::run() {
    sql.push_back(&sndr_queue);
    
    recv.start();
    sndr.start();
}

bool Client::is_dead() {
    return !is_alive;
}

void Client::kill() {
    sql.remove(&sndr_queue);
    sndr_queue.close();
    sk.close();
    recv.join();
    sndr.join();
}
