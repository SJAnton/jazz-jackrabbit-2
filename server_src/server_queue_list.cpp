#include "server_queue_list.h"

#include <iostream>


void ServerQueueList::push_back(Queue<InfoJuego> *queue, const int &id_client) {
    std::lock_guard<std::mutex> lock(m);
    map[id_client].push_back(queue);
}

void ServerQueueList::push_to_all_queues(const InfoJuego &data) {
    std::lock_guard<std::mutex> lock(m);
    for (auto &pair : map) {
        for (auto &queue : pair.second) {
            //queue->push(data);
            queue->try_push(data);
        }
    }
}

void ServerQueueList::remove(const int &id_client) {
    std::lock_guard<std::mutex> lock(m);
    map.erase(id_client);
}

int ServerQueueList::size() {
    std::unique_lock<std::mutex> lock(m);
    return map.size();
}

void ServerQueueList::clear() {
    map.clear();
}

std::map<int, std::list<Queue<InfoJuego>*>>::iterator ServerQueueList::begin() {
    return map.begin();
}

std::map <int, std::list<Queue<InfoJuego>*>>::iterator ServerQueueList::end() {
    return map.end();
}