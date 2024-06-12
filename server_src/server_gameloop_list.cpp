#include "server_gameloop_list.h"

void GameloopList::push_back(ServerGameloop *gameloop) {
    std::unique_lock<std::mutex> lock(m);
    list.push_back(gameloop);
}

void GameloopList::remove(ServerGameloop *gameloop) {
    std::unique_lock<std::mutex> lock(m);
    list.remove(gameloop);
}

int GameloopList::size() {
    std::unique_lock<std::mutex> lock(m);
    return list.size();
}

void GameloopList::clear() {
    list.clear();
}

std::list<ServerGameloop*>::iterator GameloopList::erase(std::list<ServerGameloop*>::iterator it) {
    std::unique_lock<std::mutex> lock(m);
    return list.erase(it);
}

std::list<ServerGameloop*>::iterator GameloopList::begin() {
    return list.begin();
}

std::list<ServerGameloop*>::iterator GameloopList::end() {
    return list.end();
}

/*ServerGameloop* GameloopList::find_by_id(int id) {
    std::unique_lock<std::mutex> lock(m);
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->is_id(id)) {
            return *it;
        }
    }
    return nullptr;
}*/