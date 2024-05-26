#include "server_character_map.h"

void CharacterMap::push_back(int id, Character *character) {
    std::unique_lock<std::mutex> lock(m);
    map.at(id) = character;
}

Character CharacterMap::at(int id) {
    std::unique_lock<std::mutex> lock(m);
    return *map.at(id);
}

int CharacterMap::size() {
    std::unique_lock<std::mutex> lock(m);
    map.size();
}

void CharacterMap::erase(int id) {
    std::unique_lock<std::mutex> lock(m);
    map.erase(id);
}

void CharacterMap::clear() {
    map.clear();
}

std::map<int, Character*>::iterator CharacterMap::begin() {
    return map.begin();
}

std::map<int, Character*>::iterator CharacterMap::end() {
    return map.end();
}
