#include "server_acceptor.h"

//constructor:
ServerAcceptor::ServerAcceptor(const std::string &hostname) :
    sk(hostname.c_str()),
    was_closed(false)
{

}

void ServerAcceptor::run() {
    int id = 1; // Máximo = 255 jugadores (por conversión a uint8_t)
    while (!was_closed) {
        try {
            Socket peer = sk.accept();
            clients.emplace_back(std::move(peer), id, gameloops);
            std::cout << "Se conectó el cliente " << id << std::endl;

            clients.back().start();
            //reap_dead();
            id++;
        } catch (LibError &e) {
            std::cerr << "Error en el Acceptor" << e.what() << std::endl;

        } catch (const std::exception& e) {
        
        }
    }
    kill_all();
}

void ServerAcceptor::reap_dead() {
    clients.remove_if([](Client& client) {
        if (client.is_dead()) {
            client.kill();
            return true;
        }
        return false;
    });
}

void ServerAcceptor::kill_all() {
    for (auto &client : clients) { //mato todos los clientes
        client.kill();
        client.join();
    }
    clients.clear();
    for (auto &gameloop : gameloops) { //mato todos los gameloops
        gameloop->kill();
        gameloop->join();
        delete gameloop;
    }
    gameloops.clear();
}
