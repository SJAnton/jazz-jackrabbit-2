#ifndef SERVER_CHARACTER_MAP_H_
#define SERVER_CHARACTER_MAP_H_

#include <map>
#include <mutex>
#include <memory>

#include "characters/server_character.h"

class CharacterMap {
    private:
        std::map<int, std::shared_ptr<Character>> map;

        std::mutex m;

    public:
        CharacterMap() {};

        void push_back(int id, std::shared_ptr<Character> character);

        std::shared_ptr<Character> at(int id);

        int size();

        bool empty();

        void erase(int id);

        void clear();

        std::map<int, std::shared_ptr<Character>>::iterator begin();

        std::map<int, std::shared_ptr<Character>>::iterator end();
};
#endif
