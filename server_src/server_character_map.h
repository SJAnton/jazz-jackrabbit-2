#ifndef SERVER_CHARACTER_MAP_H_
#define SERVER_CHARACTER_MAP_H_

#include <map>
#include <mutex>

#include "characters/server_character.h"

class CharacterMap {
    private:
        std::map<int, Character*> map;

        std::mutex m;

    public:
        CharacterMap() {};

        void push_back(int id, Character *character);

        Character at(int id);

        int size();

        void erase(int id);

        void clear();

        std::map<int, Character*>::iterator begin();

        std::map<int, Character*>::iterator end();
};
#endif
