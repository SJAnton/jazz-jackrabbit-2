#include "server_acceptor.h"

void ServerAcceptor::run() {
    int id = 1;
    while (!wc) {
        try {
            Socket peer = sk.accept();

            Client *client = new Client(std::move(peer), id, gmlp_id, gameloops, ch_maps,
                                            monitors, gameloops_q, data);

            client->start();
            clients.push_back(client);

            reap_dead_clients();
            id++;
        } catch (LibError &e) {

        }
    }
    kill_all();
}

void ServerAcceptor::reap_dead_clients() {
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
    for (auto &gameloop : gameloops) {
        gameloop->kill();
        gameloop->join();
        delete gameloop;
    }
    gameloops.clear();
}
