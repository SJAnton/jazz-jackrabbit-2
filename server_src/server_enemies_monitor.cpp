#include "server_enemies_monitor.h"


void ServerEnemiesMonitor::push_back(int id, std::shared_ptr<Character> character) {
    std::lock_guard<std::mutex> lock(m);
    map[id] = character;
}

std::shared_ptr<Character> ServerEnemiesMonitor::at(int id) {
    std::lock_guard<std::mutex> lock(m);
    auto it = map.find(id);
    if (it != map.end()) {
        return it->second;
    }
    return nullptr;
}

int ServerEnemiesMonitor::size() {
    std::lock_guard<std::mutex> lock(m);
    return map.size();
}

bool ServerEnemiesMonitor::is_empty() {
    std::lock_guard<std::mutex> lock(m);
    return map.empty();
}

void ServerEnemiesMonitor::erase(int id) {
    std::lock_guard<std::mutex> lock(m);
    map.erase(id);
}

void ServerEnemiesMonitor::clear() {
    std::lock_guard<std::mutex> lock(m);
    map.clear();
}

std::map<int, std::shared_ptr<Character>>::iterator ServerEnemiesMonitor::begin() {
    std::lock_guard<std::mutex> lock(m);
    return map.begin();
}

std::map<int, std::shared_ptr<Character>>::iterator ServerEnemiesMonitor::end() {
    std::lock_guard<std::mutex> lock(m);
    return map.end();
}

void ServerEnemiesMonitor::update(int id, std::shared_ptr<Character> character) {
    std::lock_guard<std::mutex> lock(m);
    map[id] = character;
}