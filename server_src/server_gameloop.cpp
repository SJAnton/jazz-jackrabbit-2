#include <chrono>
#include <thread>

#include "server_gameloop.h"

void ServerGameloop::run() {
    while (!wc) {
        // Retirar elementos de la cola del receiver, operar
        // e insertar en la cola de los senders (hacerlo en
        // ServerApp para reducir el tamaño del gameloop)
    }
}
