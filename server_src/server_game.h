#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include "server_queue.h"
#include "characters/server_character.h"

class Game {
    private:
        void move_character(uint8_t &byte, Character &character);

        void attack(uint8_t &byte, Character &character);

    public:
        Game() {};

        std::vector<uint8_t> get_actions(Queue<uint8_t> &q);

        void execute_actions(std::vector<uint8_t> &actions);
};
#endif
