#include "server_acceptor.h"

void ServerAcceptor::run() {
    int id = 0;
    while (!wc) {
        try {
            // Clase Client para la comunicación y clase Player para
            // el jugador, se puede implementar que uno tome a otro
            // como atributo
            Socket peer = sk.accept();

            // El byte inicial del client al servidor determina
            // el personaje utilizado
            Client *client = new Client(std::move(peer), id, q, sql);
            Player player;

            client->start();

            reap_dead();
            clients.push_back(client);
            id++;
        } catch (LibError &e) {

        }
    }
    kill_all();
}

void ServerAcceptor::reap_dead() {
    clients.remove_if([](Client* client) {
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
}
