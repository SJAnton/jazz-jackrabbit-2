#include "server_queue_list.h"

#include <iostream>

void ServerQueueList::push_back(Queue<uint8_t> *queue) {
    std::unique_lock<std::mutex> lock(m);
    list.push_back(queue);
}

void ServerQueueList::push_to_all_queues(uint8_t value) {
    std::unique_lock<std::mutex> lock(m);
    for (Queue<uint8_t> *queue : list) {
        queue->try_push(value);
    }
}

void ServerQueueList::remove(Queue<uint8_t> *queue) {
    std::unique_lock<std::mutex> lock(m);
    list.remove(queue);
}

std::list<Queue<uint8_t>*>::iterator ServerQueueList::begin() {
    return list.begin();
}

std::list<Queue<uint8_t>*>::iterator ServerQueueList::end() {
    return list.end();
}
