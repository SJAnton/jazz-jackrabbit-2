#ifndef SERVER_QUEUE_LIST_H_
#define SERVER_QUEUE_LIST_H_

#include <list>
#include <map>
#include <mutex>

#include "../common_src/queue.h"
#include "../common_src/info_juego.h"

/**
 * Contiene todas las sender_queues de los clientes de una partida
*/
class ServerQueueList {
    private:
        std::map<int, std::list<Queue<InfoJuego>*>> map;

        std::mutex m;

    public:
        ServerQueueList() {}

        void push_back(Queue<InfoJuego> *queue, const int &id_client);

        void push_to_all_queues(const InfoJuego &data);

        void remove(const int &id_client);

        int size();

        void clear();

        std::map<int, std::list<Queue<InfoJuego>*>>::iterator begin();

        std::map<int, std::list<Queue<InfoJuego>*>>::iterator end();
};

#endif
