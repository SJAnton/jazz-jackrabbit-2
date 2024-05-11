#ifndef SERVER_QUEUE_LIST_H_
#define SERVER_QUEUE_LIST_H_

#include <list>
#include <mutex>

#include "server_queue.h"

class ServerQueueList {
    private:
        std::list<Queue<uint8_t>*> list;

        std::mutex m;

    public:
        ServerQueueList() {}

        void push_back(Queue<uint8_t> *queue);

        /* Inserta un valor uint8_t en todas las queues */
        void push_to_all_queues(uint8_t value);

        void remove(Queue<uint8_t> *queue);

        std::list<Queue<uint8_t>*>::iterator begin();

        std::list<Queue<uint8_t>*>::iterator end();
};
#endif
