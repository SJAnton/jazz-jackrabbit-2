#ifndef SERVER_QUEUE_LIST_H_
#define SERVER_QUEUE_LIST_H_

#include <list>
#include <mutex>

#include "server_queue.h"
#include "../common_src/info_juego.h"

class ServerQueueList {
    private:
        std::list<Queue<InfoJuego>*> list;

        std::mutex m;

    public:
        ServerQueueList() {}

        void push_back(Queue<InfoJuego> *queue);

        void push_to_all_queues(InfoJuego data);

        void remove(Queue<InfoJuego> *queue);

        int size();

        std::list<Queue<InfoJuego>*>::iterator begin();

        std::list<Queue<InfoJuego>*>::iterator end();
};
#endif
