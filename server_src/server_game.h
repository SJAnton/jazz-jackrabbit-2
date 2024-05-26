#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include "server_queue.h"
#include "server_character_map.h"
#include "characters/server_character.h"

class Game {
    private:

    public:
        Game() {};

        std::vector<uint8_t> get_actions(Queue<uint8_t> &q);

        void execute_actions(std::vector<uint8_t> &actions, CharacterMap &ch_map);

        void snapshot();
};
#endif
