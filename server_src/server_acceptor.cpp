#include "server_acceptor.h"

ServerAcceptor::ServerAcceptor(Socket &socket, bool &was_closed) :
                                sk(socket), was_closed(was_closed) {}


void ServerAcceptor::run() {
    int id = 1; // Máximo = 255 jugadores (por conversión a uint8_t)
    while (!was_closed) {
        try {
            Socket peer = sk.accept();

            Client *client = new Client(std::move(peer), id, gmlp_id, gameloops);

            client->start();
            clients.push_back(client);

            reap_dead();
            id++;
        } catch (LibError &e) {

        }
    }
    kill_all();
}

void ServerAcceptor::reap_dead() {
    clients.remove_if([](Client *client) {
        if (client->is_dead()) {
            client->kill();
            client->join();
            return true;
        }
        return false;
    });
}

void ServerAcceptor::kill_all() {
    for (auto &client : clients) {
        client->kill();
        client->join();
    }
    clients.clear();
    for (auto &gameloop : gameloops) {
        gameloop->kill();
        gameloop->join();
        delete gameloop;
    }
    gameloops.clear();
}
