#ifndef SERVER_CHARACTER_LIST_H_
#define SERVER_CHARACTER_LIST_H_

#include <list>
#include <mutex>

#include "characters/server_character.h"

class CharacterList {
    private:
        std::vector<Character*> list;

        std::mutex m;

    public:
        CharacterList();

        void push_back(Character *character);

        Character at();

        void remove_by_element(int &element);

        void remove_by_id(uint8_t &id);

        std::vector<Character*>::iterator begin();

        std::vector<Character*>::iterator end();
};
#endif
