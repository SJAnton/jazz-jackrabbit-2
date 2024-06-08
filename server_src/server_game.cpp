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

    //std::cout << "x = " << (int)ch->get_x_pos() << " y = " << (int)ch->get_y_pos() << std::endl;

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
    //std::cout << "x = " << (int)ch->get_x_pos() << " y = " << (int)ch->get_y_pos() << std::endl;
}

void Game::tick(std::shared_ptr<CharacterMap> &ch_map,
                std::list<std::shared_ptr<Projectile>> &projectile_list) {
    // Mover enemigos y proyectiles
    // Implementar caída del personaje
    for (auto it = ch_map->begin(); it != ch_map->end(); it++) {
        std::shared_ptr<Character> character = it->second;
        //std::cout << "character_id = " << character->get_character_id() << std::endl; TODO: arreglar
        /*if (character.is_falling()) {
            character->fall();
        }*/
    }
    for (std::shared_ptr<Projectile> projectile : projectile_list) {
        projectile->move_x_pos();
        /* if (projectile->contact()) {
            projectile_list.remove(projectile);
        }
        */
        std::cout << (int)projectile->get_x_pos() << std::endl;    
    }
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

void Game::remove_character(uint8_t &player_id, std::shared_ptr<CharacterMap> &ch_map) {
    ch_map->erase(player_id);
}
