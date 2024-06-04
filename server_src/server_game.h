#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include "server_queue.h"
#include "server_character_map.h"
#include "characters/server_character.h"

class Game {
    private:

    public:
        Game() {};

        std::vector<uint8_t> get_actions(std::shared_ptr<Queue<uint8_t>> &q);

        void execute_actions(std::vector<uint8_t> &actions, std::shared_ptr<CharacterMap> &ch_map);

        std::map<uint8_t, std::vector<uint8_t>> snapshot(std::shared_ptr<CharacterMap> &ch_map);
};
#endif
