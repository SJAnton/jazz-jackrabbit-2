#include "server_game.h"

#include <iostream>

#define ID_POS 0
#define ACTION_POS 1
#define DIRECTION_POS 2

void Game::check_top_three_players(std::vector<Character> top_players) {
    /*if (top_players[2] > top_players[1]) {
        std::swap(top_players[1], top_players[2]);
    }
    if (top_players[1] > top_players[0]) {
        std::swap(top_players[0], top_players[1]);
    }*/
}

std::vector<uint8_t> Game::get_actions(std::shared_ptr<Queue<uint8_t>> &q) {
    std::vector<uint8_t> data;
    uint8_t byte;
    while (q->try_pop(byte)) {
        data.push_back(byte);
    }
    return data;
}

void Game::execute_actions(std::vector<uint8_t> &actions, std::shared_ptr<CharacterMap> &ch_map,
                            std::list<std::shared_ptr<Projectile>> &projectile_list,
                             std::map<std::string, std::vector<uint8_t>> &data_map) {
    if (actions.empty()) {
        return;
    }
    uint8_t player_id = actions[ID_POS];
    uint8_t action = actions[ACTION_POS];
    uint8_t direction = actions[DIRECTION_POS];

    std::shared_ptr<Character> ch = ch_map->at(player_id);

    switch (action) {
        case ACTION_IDLE:
            ch->do_nothing();
            break;
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
            ch->attack(direction, projectile_list, data_map);
            break;
        case ACTION_SPECIAL_ATTACK:
            ch->special_attack();
            break;
        default:
            break;
    }
}

void Game::tick(std::shared_ptr<CharacterMap> &ch_map,
                std::list<std::shared_ptr<Projectile>> &projectile_list) {
    for (auto it = ch_map->begin(); it != ch_map->end(); ++it) {
        std::shared_ptr<Character> character = it->second;
        if (character->is_intoxicated()) {
            character->reduce_intoxicated_time();
        }
        //check_top_three_players(character);
        /*if (character.is_falling()) {
            character->fall();
        }*/
    }
    for (std::shared_ptr<Projectile> projectile : projectile_list) {
        uint8_t current_x_pos = projectile->get_x_pos();
        projectile->move_x_pos();
        /*if (current_x_pos == 0 || current_x_pos == 255) {
            projectile_list.remove(projectile);
            continue;
        }*/
        /* if (projectile->contact()) {
            projectile_list.remove(projectile);
        }
        */
    }
}

InfoJuego Game::snapshot(std::shared_ptr<CharacterMap> &ch_map) {
    std::vector<InfoPlayer> players_data;
    std::vector<InfoEnemigo> enemies_data;
    std::vector<InfoRecolectable> items_data;
    std::vector<InfoProyectil> projectile_data;

    for (auto it = ch_map->begin(); it != ch_map->end(); ++it) {
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

void Game::remove_character(uint8_t &player_id, std::shared_ptr<CharacterMap> &ch_map) {
    ch_map->erase(player_id);
}
