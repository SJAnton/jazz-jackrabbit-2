#include "server_game.h"

#define MSG_SIZE 3

#define ID_POS 0
#define ACTION_POS 1
#define DIRECTION_POS 2

#define ACTION_WALK 0x12
#define ACTION_RUN 0x13
#define ACTION_JUMP 0x14
#define ACTION_SHOOT 0x15
#define ACTION_SPECIAL_ATTACK 0x16

std::vector<uint8_t> Game::get_actions(Queue<uint8_t> &q) {
    std::vector<uint8_t> data;
    for (int i = 0; i < MSG_SIZE; i++) {
        data.push_back(q.pop());
    }
    return data;
}

void Game::execute_actions(std::vector<uint8_t> &actions, CharacterMap &ch_map) {
    uint8_t player_id = actions[ID_POS];
    uint8_t action = actions[ACTION_POS];
    uint8_t direction = actions[DIRECTION_POS];

    Character ch = ch_map.at(player_id);

    switch (action) {
        case ACTION_WALK:
            ch.move_x_pos(action, direction);
            break;
        case ACTION_RUN:
            ch.move_x_pos(action, direction);
            break;
        case ACTION_JUMP:
            ch.jump();
            break;
        case ACTION_SHOOT:
            ch.attack();
            break;
        case ACTION_SPECIAL_ATTACK:
            ch.special_attack();
            break;
        default:
            break;
    }
}

std::map<uint8_t, std::vector<uint8_t>> Game::snapshot(CharacterMap &ch_map) {
    std::map<uint8_t, std::vector<uint8_t>> game_data;
    /*for (auto &it : ch_map) {
        int character_id = it.first;
        Character *character = it.second;
        std::vector<uint8_t> character_data;

        // Llenar ch_data

        game_data.at(character_id) = character_data;
    }*/
    return game_data;
}
