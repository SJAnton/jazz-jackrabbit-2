#include "server_acceptor.h"

void ServerAcceptor::run() {
    while (!wc) {
        try {
            Socket peer = sk.accept();

            Client *client = new Client(std::move(peer), q, sql);
            client->start();

            reap_dead();
            clients.push_back(client);
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
