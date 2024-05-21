#include "server_acceptor.h"

#define GAME_BYTE 0
#define CHAR_BYTE 0
#define GAME_JOINED_BYTE 0

#define NEW_GAME 0

#define JAZZ_CODE "PlayerJazz"
#define LORI_CODE "PlayerLori"
#define SPAZ_CODE "PlayerSpaz"

void ServerAcceptor::run() {
    int id = 0;
    while (!wc) {
        try {
            Socket peer = sk.accept();

            // El protocol se crea para leer el primer mensaje con la
            // información relacionada (cuál personaje se eligió y si
            // creó una nueva partida o se unió a una existente) y
            // para enviar el estado de las partidas y cuáles escenarios
            // están disponibles
            ServerProtocol pr(peer);

            std::vector<uint8_t> game_info;
            game_info.push_back(gameloops.size());
            //game_info.push_back(escenarios);

            // Información de inicio
            pr.send_msg(game_info, wc);
            std::vector<uint8_t> init_data = pr.recv_init_msg(wc);

            // Se crea una nueva partida y el client recibe la cola única
            // de este gameloop y su lista de colas para enviarle acciones.
            // Los gameloops a su vez se guardan en una lista de gameloops
            // del aceptador.
            Queue<uint8_t> recv_q;
            ServerQueueList sql;

            // El byte inicial del client al servidor determina
            // el personaje utilizado
            Character ch = app.choose_character(init_data[CHAR_BYTE], data);

            Client *client;

            if (init_data[GAME_BYTE] == NEW_GAME) {
                bool gmlp_wc = false;
                ServerGameloop *gameloop = new ServerGameloop(recv_q, sql, std::move(gmlp_wc));
                
                rql.push_back(recv_q); // Ambos tienen el
                sqll.push_back(sql);   // mismo índice

                gameloop->start();
                gameloops.push_back(gameloop);

                client = new Client(std::move(peer), std::move(ch), id, recv_q, sql);
            } else {
                // El gameloop ya existe, hay que obtener la cola única
                // y la lista de colas del gameloop existente para
                // construir al client.
                client = new Client(std::move(peer), std::move(ch), id,
                                    rql.at(GAME_JOINED_BYTE), sqll.at(GAME_JOINED_BYTE));
            }
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
