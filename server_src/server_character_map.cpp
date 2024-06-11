#include "server_character_map.h"

void CharacterMap::push_back(int id, std::shared_ptr<Character> &character) {
    std::unique_lock<std::mutex> lock(m);
    map[id] = character;
}

std::shared_ptr<Character> CharacterMap::at(int id) {
    std::unique_lock<std::mutex> lock(m);
    return map.at(id);
}

int CharacterMap::size() {
    std::unique_lock<std::mutex> lock(m);
    return map.size();
}

bool CharacterMap::empty() {
    std::unique_lock<std::mutex> lock(m);
    return map.empty();
}

void CharacterMap::erase(int id) {
    std::unique_lock<std::mutex> lock(m);
    map.erase(id);
}

void CharacterMap::clear() {
    map.clear();
}

std::map<int, std::shared_ptr<Character>>::iterator CharacterMap::begin() {
    return map.begin();
}

std::map<int, std::shared_ptr<Character>>::iterator CharacterMap::end() {
    return map.end();
}
