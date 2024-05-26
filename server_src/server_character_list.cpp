#include "server_character_list.h"

void CharacterList::push_back(Character *character) {
    std::unique_lock<std::mutex> lock(m);
    list.push_back(character);
}

void CharacterList::remove_by_element(int &element) {
    std::unique_lock<std::mutex> lock(m);
    list.erase(list.begin() + element);
}

void CharacterList::remove_by_id(uint8_t &id) {
    std::unique_lock<std::mutex> lock(m);
    /*for (Character *ch : list) {
        if (ch)
    }*/
}

std::vector<Character*>::iterator CharacterList::begin() {
    return list.begin();
}

std::vector<Character*>::iterator CharacterList::end() {
    return list.end();
}
