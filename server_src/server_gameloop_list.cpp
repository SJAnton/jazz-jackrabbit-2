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

bool GameloopList::contains(int id) {
    std::lock_guard<std::mutex> lock(m);
    for (auto gameloop : list) {
        if (gameloop->id == id) {
            return true;
        }
    }
    return false;
}

ServerGameloop* GameloopList::at(int id) {
    std::lock_guard<std::mutex> guard(m);
    for (auto gameloop : list) {
        if (gameloop->id == id) {
            return gameloop;
        }
    }
    return nullptr; // Devuelve nullptr si no se encuentra el gameloop
}
