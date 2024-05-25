#include "server_acceptor.h"

void ServerAcceptor::run() {
    int id = 0;
    while (!wc) {
        try {
            Socket peer = sk.accept();
            
            Client *client = new Client(std::move(peer), id, gameloops,
                                            monitors, gameloops_q, data);

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
    clients.remove_if([](Client* client) {
        if (client->is_dead()) {
            client->kill();
            client->join();
            delete client;
        }
    });
    gameloops.remove_if([](ServerGameloop* gameloop) {
        if (gameloop->is_dead()) {
            gameloop->kill();
            gameloop->join();
            delete gameloop;
        }
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