#ifndef SERVER_CLIENT_H_
#define SERVER_CLIENT_H_

#include "server_queue.h"
#include "server_thread.h"
#include "server_sender.h"
#include "server_gameloop.h"
#include "server_receiver.h"
#include "server_queue_list.h"
#include "../common_src/socket.h"
#include "../common_src/liberror.h"
#include "characters/server_player_jazz.h"
#include "characters/server_player_lori.h"
#include "characters/server_player_spaz.h"

class Client : public Thread {
    private:    
        // ESTA DATA LA RECIBIMOS POR PARAMETRO EN EL CONSTRUCTOR
        Socket sk;

        int id;

        std::list<ServerGameloop*> &gameloops;

        //std::vector<ServerQueueList> &monitors;

        //std::vector<Queue<uint8_t>> &gameloops_q;

        std::map<uint8_t, std::vector<ServerQueueList>> &monitors;

        std::map<uint8_t, std::vector<Queue<uint8_t>>> &gameloops_q;

        std::map<std::string, std::vector<uint8_t>> &data;

        ServerProtocol protocol;

        // ESTA DATA LA CREAMOS EN EL CONSTRUCTOR
        Queue<uint8_t> sndr_q;

        std::shared_ptr<Queue<uint8_t>> recv_q;

        std::shared_ptr<ServerQueueList> monitor;

        std::unique_ptr<Character> player;

        ServerReceiver recv;

        ServerSender sndr;

        bool wc = false;

        void select_game(uint8_t game, uint8_t game_joined);

        void select_character(uint8_t character);

    public:
        Client(Socket socket, int id, std::list<ServerGameloop*> &gameloops,
                //std::vector<ServerQueueList> &monitors, std::vector<Queue<uint8_t>> &gameloops_q,
                std::map<uint8_t, std::vector<ServerQueueList>> &monitors,
                std::map<uint8_t, std::vector<Queue<uint8_t>>> &gameloops_q,
                    std::map<std::string, std::vector<uint8_t>> &data) :
                    sk(std::move(socket)), id(id), gameloops(gameloops), monitors(monitors),
                        gameloops_q(gameloops_q), protocol(sk), recv(protocol, recv_q, wc),
                            sndr(protocol, sndr_q, wc), data(data) {}

        void run() override;

        int get_id();

        Character get_player();

        bool is_dead();

        void kill();
};
#endif
