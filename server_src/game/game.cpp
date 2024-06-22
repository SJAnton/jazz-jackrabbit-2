#include "game.h"

#include <iostream>

#include "../../common_src/constantes_protocolo.h"

#define ID_POS 0
#define ACTION_POS 1
#define DIRECTION_POS 2

#define TOP_NUM 3
#define TOP_LAST_POS 2

#define PLAYER_CODE "ObjectPlayer"
#define PROJECTILE_CODE "ObjectProjectile"
#define COLLECTED_CODE "ObjectCollected"
#define BAT_CODE "EnemyBat"
#define DIABLO_CODE "EnemyDiablo"
#define RAT_CODE "EnemyRat"

//Metodo para cargar todas las constantes del config
void Game::init(std::map<std::string, std::vector<uint8_t>> &data) {
    std::vector<uint8_t> &player_data = data[PLAYER_CODE];
    std::vector<uint8_t> &projectile_data = data[PROJECTILE_CODE];
    std::vector<uint8_t> &collected_data = data[COLLECTED_CODE];
    std::vector<uint8_t> &bat_data = data[BAT_CODE];
    std::vector<uint8_t> &diablo_data = data[DIABLO_CODE];
    std::vector<uint8_t> &rat_data = data[RAT_CODE];

    ObjectPlayer::init(
        player_data[0], player_data[1], player_data[2],
        player_data[3], player_data[4], player_data[5]
    );

    ObjectProjectile::init(
        projectile_data[0], projectile_data[1], projectile_data[2], projectile_data[3],
        projectile_data[4], projectile_data[5], projectile_data[6], projectile_data[7]
    );

    ObjectCollected::init(
        collected_data[0], collected_data[1], collected_data[2],
        collected_data[3], collected_data[4], collected_data[5]
    );

    EnemyBat::init(
        bat_data[0], bat_data[1], bat_data[2], bat_data[3], bat_data[4], bat_data[5], bat_data[6]
    );

    EnemyDiablo::init(
        diablo_data[0], diablo_data[1], diablo_data[2], diablo_data[3],
        diablo_data[4], diablo_data[5], diablo_data[6]
    );

    EnemyRat::init(
        rat_data[0], rat_data[1], rat_data[2], rat_data[3], rat_data[4], rat_data[5], rat_data[6]
    );
} 

Game::Game() : 
    ch_map(std::make_shared<PlayerMap>()), 
    gameMundo(ch_map->getPlayers(), enemies, itemsRecolectables) 
{
    //Hardcodeo 2 monedas (esta info debo recibirla en init y guardarmela en una variable estatica privada)
    itemsRecolectables.push_back(ObjectCollected(Moneda));
    itemsRecolectables.back().setPosition(Coordenada(250, 225));

    itemsRecolectables.push_back(ObjectCollected(Moneda));
    itemsRecolectables.back().setPosition(Coordenada(350, 220));
}

// Se llama en cada iteracion del gameloop.
void Game::execute_actions(std::vector<uint8_t> &actions) {
    //chequeo los estados de cada player
    std::vector<std::shared_ptr<ObjectPlayer>> players = ch_map->getPlayers();
    for (auto &p : players) {
        if (p->is_dead()) {
            p->updateDeath();
        }
        else if (p->isJumping()) {
            p->updateJump();
        }
        else if (p->getEstado() == EstadosPlayer::Shooting) {
            p->updateShoot();
        }
    } 
    if (actions.empty()) {
        for (auto &p : players) {
            if (!p->isJumping() && !p->is_falling()) {
                p->idle();
            }
        }
        return;
    }
    uint8_t player_id = actions[ID_POS];
    uint8_t action = actions[ACTION_POS];
    Direcciones direction = Right;

    if (actions[DIRECTION_POS] == LEFT) {
        direction = Left;
    } else if (ch_map->count(player_id) == 0) {
        return;
    }
    std::shared_ptr<ObjectPlayer> player = ch_map->at(player_id); //identifico el player por su id

    switch (action) {
        case ACTION_WALK:
            player->walk(direction);
            break;
        case ACTION_RUN:
            player->run(direction);
            break;
        case ACTION_JUMP:
            player->jump(direction);
            break;
        case ACTION_SHOOT: {
            try {
                ObjectProjectile proyectil = player->shoot(direction);
                gameMundo.addProjectile(std::move(proyectil));
            } catch(const NoAmmoException& e) {
                std::cout << "sin balas" << std::endl;
            }
            break;
        }
        case ACTION_CHANGE_WEAPON:
            player->change_shooting_weapon();
            break;
        //case ACTION_SPECIAL_ATTACK:
            //player->special_attack();
            //break;
        default:
            break;
    }
}
void Game::update() {
    update_top_players();
    gameMundo.update();
}

InfoJuego Game::snapshot() {
    std::vector<InfoPlayer> players_data;
    std::vector<InfoEnemigo> enemies_data;
    std::vector<InfoRecolectable> items_data;

    for (auto it = ch_map->begin(); it != ch_map->end(); ++it) {
        std::shared_ptr<ObjectPlayer> &Player = it->second;

        InfoPlayer player_data = Player->getInfo();
        players_data.push_back(player_data);
    }
    for (auto &enemy : enemies) {
        InfoEnemigo info = enemy->getInfo();
        enemies_data.push_back(info);
    }
    for (auto &item : itemsRecolectables) {
        if (item.isCollected())
            continue;
        InfoRecolectable info = item.getInfo();
        items_data.push_back(info);
    }
    InfoJuego game_data(players_data, enemies_data, items_data, gameMundo.getInfoProyectiles());
    return game_data;
}

bool Game::compare_points(std::shared_ptr<ObjectPlayer> &pl1, std::shared_ptr<ObjectPlayer> &pl2) {
    return pl1->get_points() > pl2->get_points();
}

void Game::update_top_players() {
    std::vector<std::shared_ptr<ObjectPlayer>> players = ch_map->getPlayers();
    for (auto &player : players) {
        if (std::count(top_players.begin(), top_players.end(), player) == 0) {
            // Character no está en la lista
            if (top_players.size() < TOP_NUM) {
                top_players.push_back(player);
            } else if (player->get_points() > top_players[TOP_LAST_POS]->get_points()) {
                top_players[TOP_LAST_POS] = player;
            }
        }
        std::sort(top_players.begin(), top_players.end(), Game::compare_points);
    }
}

void Game::add_player(TipoPlayer &player_type, int player_id) {
    std::shared_ptr<ObjectPlayer> player = std::make_shared<ObjectPlayer>(
        player_id, player_type, Weapon(TipoArma::Tipo_1)
    );
    ch_map->push_back(player_id, player);
    std::cout << "agrego player al juego" << std::endl;

    gameMundo.addPlayer(player, Coordenada(70, 50));
}

void Game::remove_player(const int &player_id) {
    ch_map->erase(player_id);
}

bool Game::is_running() {
    return _is_running;
}

void Game::stop() {
    _is_running = false;
}
