#include "game.h"

#include <iostream>

#define ID_POS 0
#define ACTION_POS 1
#define DIRECTION_POS 2

#include "../../common_src/constantes_protocolo.h"

Game::Game() : 
    ch_map(std::make_shared<PlayerMap>()), 
    gameMundo(ch_map->getPlayers(), itemsRecolectables) 
{
    //Hardcodeo 2 monedas
    itemsRecolectables.push_back(ObjectCollected(Moneda));
    itemsRecolectables.back().setPosition(Coordenada(250, 225));

    itemsRecolectables.push_back(ObjectCollected(Moneda));
    itemsRecolectables.back().setPosition(Coordenada(350, 220));

}


std::vector<uint8_t> Game::get_actions(std::shared_ptr<Queue<uint8_t>> &q) {
    std::vector<uint8_t> data;
    uint8_t byte;
    while (q->try_pop(byte)) {
        data.push_back(byte);
    }
    return data;
}

void Game::execute_actions(std::vector<uint8_t> &actions) {
    if (actions.empty()) {
        return;
    }
    uint8_t player_id = actions[ID_POS];
    uint8_t action = actions[ACTION_POS];
   
   Direcciones direction = Right;
    if (actions[DIRECTION_POS] == LEFT)
         direction = Left;

    std::shared_ptr<ObjectPlayer> player = ch_map->at(player_id); //identifico el player por su id
    //std::cout << "Ejecuto accion" << std::endl;
    switch (action) {
        case ACTION_IDLE:
           // player->do_nothing();
            break;
        case ACTION_WALK:
            player->walk(direction);
            break;
        case ACTION_RUN:
            player->run(direction);
            break;
        case ACTION_JUMP:
            player->jump(direction);
            break;
        case ACTION_SHOOT:
            player->shoot(direction);
            break;
        case ACTION_SPECIAL_ATTACK:
            //player->special_attack();
            break;
        default:
            break;
    }
}
void Game::update() {
    gameMundo.update();
}

/*void Game::tick() {
    for (auto it = ch_map->begin(); it != ch_map->end(); it++) {
        std::shared_ptr<ObjectPlayer> Player = it->second;
        if (Player.is_falling()) {
            Player->fall();
        }
    }
    for (std::shared_ptr<ObjectPlayerProjectile> projectile : projectile_list) {
        projectile->move_x_pos();
        if (projectile->contact()) {
            projectile_list.remove(projectile);
        }
        
    }
}
*/

InfoJuego Game::snapshot() {
    std::vector<InfoPlayer> players_data;
    std::vector<InfoEnemigo> enemies_data;
    std::vector<InfoRecolectable> items_data;
    std::vector<InfoProyectil> projectile_data;

    for (auto it = ch_map->begin(); it != ch_map->end(); it++) {
        std::shared_ptr<ObjectPlayer> &Player = it->second;

        InfoPlayer player_data = Player->getInfo();
        players_data.push_back(player_data);
    }
    for (auto item : itemsRecolectables) {
        if (item.isCollected())
            continue;
        InfoRecolectable info = item.getInfo();
        items_data.push_back(info);
    }
    InfoJuego game_data(players_data, enemies_data, items_data, projectile_data);
    return game_data;
}

void Game::send_snapshot(ServerQueueList &sndr_qs) {
    InfoJuego game_data = snapshot();
    sndr_qs.push_to_all_queues(game_data);
}

void Game::add_player(TipoPlayer &player_type, int player_id) {
    std::shared_ptr<ObjectPlayer> player = std::make_shared<ObjectPlayer>(player_id, player_type, Weapon(10,TipoArma::Blaster));
    ch_map->push_back(player_id, player);
    std::cout << "agrego player al juego" << std::endl;

    gameMundo.addPlayer(player, player->getPosition());
}

void Game::remove_player(uint8_t &player_id) {
    ch_map->erase(player_id);
}

bool Game::is_running() {
    return _is_running;
}

