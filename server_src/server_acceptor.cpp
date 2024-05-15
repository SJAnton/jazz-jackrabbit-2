#include "server_acceptor.h"

#define NEW_GAME 0

#define JAZZ 0
#define LORI 0
#define SPAZ 0

void ServerAcceptor::run() {
    int id = 0;
    while (!wc) {
        try {
            // Clase Client para la comunicación y clase Player para
            // el jugador, se puede implementar que uno tome a otro
            // como atributo
            Socket peer = sk.accept();

            // El protocol se crea para leer el primer mensaje con la
            // información relacionada (cuál personaje se eligió y si
            // creó una nueva partida o se unió a una existente)
            ServerProtocol pr(peer);

            // Información de inicio
            std::vector<uint8_t> init_data = pr.recv_init_info();

            // Se crea una nueva partida y el client recibe la cola única
            // de este gameloop y su lista de colas para enviarle acciones.
            // Los gameloops a su vez se guardan en una lista de gameloops
            // del aceptador.
            Queue<uint8_t> recv_q;
            ServerQueueList sql;

            if (/*init_data[byte_juego] == */NEW_GAME) {
                bool gmlp_wc = false;
                ServerGameloop *gameloop = new ServerGameloop(recv_q, sql, std::move(gmlp_wc));
                
                recv_q_list.push_back(recv_q); // Ambos tienen el
                sql_list.push_back(sql);       // mismo índice

                gameloop->start();
                gameloops.push_back(gameloop);
            } else {
                // El gameloop ya existe, hay que obtener la cola única
                // y la lista de colas del gameloop existente para
                // construir al client.
                recv_q /*= recv_q_list.at()*/;
                sql /*= sql_list.at()*/;
            }

            // El byte inicial del client al servidor determina
            // el personaje utilizado
            Character ch;
            if (/*init_data[byte_pj] == */JAZZ) {
                PlayerJazz player;
                ch = player;
            } else if (/*init_data[byte_pj] == */LORI) {
                PlayerLori player;
                ch = player;
            } else {
                PlayerSpaz player;
                ch = player;
            }
            Client *client = new Client(std::move(peer), std::move(ch), id, recv_q, sql);

            client->start();
            clients.push_back(client);

            reap_dead(); // También debe borrar los gameloops
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
