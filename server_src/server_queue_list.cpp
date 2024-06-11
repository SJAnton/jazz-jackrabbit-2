#include "server_queue_list.h"

#include <iostream>

void ServerQueueList::push_back(Queue<InfoJuego> *queue) {
    std::unique_lock<std::mutex> lock(m);
    list.push_back(queue);
}

void ServerQueueList::push_to_all_queues(InfoJuego data) {
    std::unique_lock<std::mutex> lock(m);
    for (Queue<InfoJuego> *queue : list) {
        queue->try_push(data);
    }
}

void ServerQueueList::remove(Queue<InfoJuego> *queue) {
    std::unique_lock<std::mutex> lock(m);
    list.remove(queue);
}

int ServerQueueList::size() {
    std::unique_lock<std::mutex> lock(m);
    return list.size();
}

std::list<Queue<InfoJuego>*>::iterator ServerQueueList::begin() {
    return list.begin();
}

std::list<Queue<InfoJuego>*>::iterator ServerQueueList::end() {
    return list.end();
}
