#include "server_character_map.h"

void PlayerMap::push_back(int id, std::shared_ptr<ObjectPlayer> &character) {
    std::unique_lock<std::mutex> lock(m);
    map[id] = character;
}

std::shared_ptr<ObjectPlayer> PlayerMap::at(int id) {
    std::unique_lock<std::mutex> lock(m);
    return map.at(id);
}

int PlayerMap::size() {
    std::unique_lock<std::mutex> lock(m);
    return map.size();
}

bool PlayerMap::empty() {
    std::unique_lock<std::mutex> lock(m);
    return map.empty();
}

void PlayerMap::erase(int id) {
    std::unique_lock<std::mutex> lock(m);
    map.erase(id);
}

void PlayerMap::clear() {
    map.clear();
}

std::map<int, std::shared_ptr<ObjectPlayer>>::iterator PlayerMap::begin() {
    return map.begin();
}

std::map<int, std::shared_ptr<ObjectPlayer>>::iterator PlayerMap::end() {
    return map.end();
}

std::vector<std::shared_ptr<ObjectPlayer>> PlayerMap::getPlayers() {
    std::lock_guard<std::mutex> lock(m);
    std::vector<std::shared_ptr<ObjectPlayer>> players;
    for (const auto &pair : map) {
        players.push_back(pair.second);
    }
    return players;
}

