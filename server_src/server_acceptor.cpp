#include "server_acceptor.h"

ServerAcceptor::ServerAcceptor(Socket &socket, int game_time, bool &was_closed) :
                                sk(socket), game_time(game_time), was_closed(was_closed) {}


void ServerAcceptor::run() {
    int id = 1; // Máximo = 255 jugadores (por conversión a uint8_t)
    while (!was_closed) {
        try {
            Socket peer = sk.accept();

            reap_dead();

            Client *client = new Client(std::move(peer), id, game_time, gmlp_id, gameloops);

            client->start();
            clients.push_back(client);

            //reap_dead();
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
            delete client;
            return true;
        }
        return false;
    });
}

void ServerAcceptor::kill_all() {
    for (auto &client : clients) {
        client->kill();
        client->join();
        delete client;
    }
    clients.clear();
    for (auto &gameloop : gameloops) {
        gameloop->kill();
        gameloop->join();
        delete gameloop;
    }
    gameloops.clear();
}
