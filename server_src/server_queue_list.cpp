#include "server_queue_list.h"

#include <iostream>

void ServerQueueList::push_back(Queue<QueueData> *queue) {
    std::unique_lock<std::mutex> lock(m);
    list.push_back(queue);
}

void ServerQueueList::push_to_all_queues(QueueData data) {
    std::unique_lock<std::mutex> lock(m);
    for (Queue<QueueData> *queue : list) {
        queue->try_push(data);
    }
}

void ServerQueueList::remove(Queue<QueueData> *queue) {
    std::unique_lock<std::mutex> lock(m);
    list.remove(queue);
}

int ServerQueueList::size() {
    std::unique_lock<std::mutex> lock(m);
    return list.size();
}

std::list<Queue<QueueData>*>::iterator ServerQueueList::begin() {
    return list.begin();
}

std::list<Queue<QueueData>*>::iterator ServerQueueList::end() {
    return list.end();
}
