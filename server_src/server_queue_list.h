#ifndef SERVER_QUEUE_LIST_H_
#define SERVER_QUEUE_LIST_H_

#include <list>
#include <mutex>
#include <variant>

#include "server_queue.h"
#include "../common_src/info_juego.h"

using QueueData = std::variant<InfoJuego, uint8_t>;

class ServerQueueList {
    private:
        //std::list<Queue<InfoJuego>*> list;

        std::list<Queue<QueueData>*> list;

        std::mutex m;

    public:
        ServerQueueList() {}

        /*void push_back(Queue<InfoJuego> *queue);

        void push_to_all_queues(InfoJuego data);

        void remove(Queue<InfoJuego> *queue);

        int size();

        std::list<Queue<InfoJuego>*>::iterator begin();

        std::list<Queue<InfoJuego>*>::iterator end();*/

        void push_back(Queue<QueueData> *queue);

        void push_to_all_queues(QueueData data);

        void remove(Queue<QueueData> *queue);

        int size();

        std::list<Queue<QueueData>*>::iterator begin();

        std::list<Queue<QueueData>*>::iterator end();
};
#endif
