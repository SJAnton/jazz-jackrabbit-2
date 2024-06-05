#include "server_game.h"

#include <iostream>

#define ID_POS 0
#define ACTION_POS 1
#define DIRECTION_POS 2

#define ACTION_WALK 0x12
#define ACTION_RUN 0x13
#define ACTION_JUMP 0x14
#define ACTION_SHOOT 0x15
#define ACTION_SPECIAL_ATTACK 0x16

#define CLOSED_GAME_MSG 0xFF

std::vector<uint8_t> Game::get_actions(std::shared_ptr<Queue<uint8_t>> &q) {
    std::vector<uint8_t> data;
    uint8_t byte;
    while (q->try_pop(byte)) {
        data.push_back(byte);
    }
    return data;
}

void Game::execute_actions(std::vector<uint8_t> &actions, std::shared_ptr<CharacterMap> &ch_map) {
    if (actions.empty()) {
        return;
    }
    uint8_t player_id = actions[ID_POS];
    uint8_t action = actions[ACTION_POS];
    uint8_t direction = actions[DIRECTION_POS];

    std::shared_ptr<Character> ch = ch_map->at(player_id);

    //std::cout << (int)ch->get_x_pos() << std::endl;

    switch (action) {
        case ACTION_WALK:
            ch->move_x_pos(action, direction);
            break;
        case ACTION_RUN:
            ch->move_x_pos(action, direction);
            break;
        case ACTION_JUMP:
            ch->jump();
            break;
        case ACTION_SHOOT:
            ch->attack();
            break;
        case ACTION_SPECIAL_ATTACK:
            ch->special_attack();
            break;
        default:
            break;
    }
    //std::cout << (int)ch->get_x_pos() << std::endl;
}

void Game::tick() {

}

InfoJuego Game::snapshot(std::shared_ptr<CharacterMap> &ch_map) {
    std::vector<InfoPlayer> players_data;
    std::vector<InfoEnemigo> enemies_data;
    std::vector<InfoRecolectable> items_data;
    std::vector<InfoProyectil> projectile_data;

    for (auto it = ch_map->begin(); it != ch_map->end(); it++) {
        int character_id = it->first;
        std::shared_ptr<Character> character = it->second;

        InfoPlayer player_data = character->set_data(character_id);
        players_data.push_back(player_data);
    }
    InfoJuego game_data(players_data, enemies_data, items_data, projectile_data);
    return game_data;
}

void Game::send_snapshot(InfoJuego &game_data, std::shared_ptr<ServerQueueList> &sndr_qs) {
    sndr_qs->push_to_all_queues(game_data);
}
