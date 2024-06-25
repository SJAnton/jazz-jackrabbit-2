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
#define WEAPON_CODE "Weapon"
#define BAT_CODE "EnemyBat"
#define DIABLO_CODE "EnemyDiablo"
#define RAT_CODE "EnemyRat"
#define GAME_KEY "Game"

int Game::timeLeftInit = 0;

//Metodo para cargar todas las constantes del config
void Game::init(std::map<std::string, std::vector<int>> &data) {
    timeLeftInit = data[GAME_KEY][0];

    std::vector<int> &player_data = data[PLAYER_CODE];
    std::vector<int> &projectile_data = data[PROJECTILE_CODE];
    std::vector<int> &collected_data = data[COLLECTED_CODE];
    std::vector<int> &weapon_data = data[WEAPON_CODE];
    std::vector<int> &bat_data = data[BAT_CODE];
    std::vector<int> &diablo_data = data[DIABLO_CODE];
    std::vector<int> &rat_data = data[RAT_CODE];

    ObjectPlayer::init(
        player_data[0], player_data[1], player_data[2], player_data[3],
        player_data[4], player_data[5], player_data[6]
    );

    ObjectProjectile::init(
        projectile_data[0], projectile_data[1], projectile_data[2], projectile_data[3],
        projectile_data[4], projectile_data[5], projectile_data[6], projectile_data[7]
    );

    ObjectCollected::init(
        collected_data[0], collected_data[1], collected_data[2],
        collected_data[3], collected_data[4], collected_data[5]
    );

    Weapon::init(weapon_data[0], weapon_data[1], weapon_data[2], weapon_data[3]);

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


Game::Game(Level &level) : ch_map(std::make_shared<PlayerMap>()), 
                           gameMundo(ch_map->getPlayers(), enemies, itemsRecolectables, level),
                           timeleft(timeLeftInit) {
    std::vector<std::shared_ptr<ObjectEnemy>> &levelEnemies = level.enemies;
    std::vector<ObjectCollected> &levelObjects = level.objects;
    for (auto &enemy : levelEnemies) {
        // Posición seteada en el reader
        enemies.push_back(enemy);
    }
    for (auto &object : levelObjects) {
        itemsRecolectables.push_back(object);
    }
};

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
        else if (p->is_doing_specialAttack()) {
            p->updateSpecialAttack();
        }
        p->updateShootingDelay();
        p->updateDamageWaitTime();
    } 
    if (actions.empty()) {
        for (auto &p : players) {
            if (p->is_dead()) {
                continue;
            } else if (!p->isJumping() && !p->is_falling()) {
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
    std::shared_ptr<ObjectPlayer> player = ch_map->at(player_id); // identifico el player por su id

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
                if (!player->get_weapon().canShoot()) {
                    return;
                }/* else if (player->getEstado() == EstadosPlayer::Walking) {
                    // Caminar y disparar a la vez
                    //--> bug si suelto la tecla de movimiento y sigo disparando
                    player->walk(direction);
                } else if (player->getEstado() == EstadosPlayer::Running) {
                    player->run(direction);
                }*/
                ObjectProjectile proyectil = player->shoot(direction);
                gameMundo.addProjectile(std::move(proyectil));
            } catch(const NoAmmoException& e) {
                std::cout << "sin balas" << std::endl;
            }
            break;
        }
        case ACTION_CHANGE_WEAPON:
            player->change_weapon();
            break;
        case ACTION_SPECIAL_ATTACK:
            player->specialAttack();
            break;
        default:
            break;
    }
}

void Game::update() {
    update_top_players();
    gameMundo.update();
}

void Game::minusTimeLeft() {
    timeleft--;
}
int Game::getTimeLeft() {
   return timeleft;
}

InfoJuego Game::snapshot() {
    std::vector<InfoPlayer> players_data;
    std::vector<InfoEnemigo> enemies_data;
    std::vector<InfoRecolectable> items_data;
    std::vector<InfoTabla> ranking_data;



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

    for (auto &p : top_players) {
        InfoTabla info(p->get_id(), p->get_TipoPlayer(), p->get_points());
        ranking_data.push_back(info);
    }

    InfoJuego game_data(players_data, enemies_data, items_data, gameMundo.getInfoProyectiles(), ranking_data, timeleft);
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
    // TODO: borrar al debuggear carga de mapas
    std::shared_ptr<ObjectPlayer> player;
    switch (player_type) {
        case Spaz : 
            player = std::make_shared<PlayerSpaz>(player_id);
            break;
        case Jazz:
            player = std::make_shared<PlayerJazz>(player_id);
            break;
        case Lori:            
            player = std::make_shared<PlayerLori>(player_id);
            break;
    }
     
    ch_map->push_back(player_id, player);
    std::cout << "agrego player al juego" << std::endl;

    gameMundo.addPlayer(player, Coordenada(70, 50));
}

void Game::add_player(TipoPlayer &player_type, int player_id, Coordenada spawn) {
    std::shared_ptr<ObjectPlayer> player;
    switch (player_type) {
        case Spaz : 
            player = std::make_shared<PlayerSpaz>(player_id);
            break;
        case Jazz:
            player = std::make_shared<PlayerJazz>(player_id);
            break;
        case Lori:            
            player = std::make_shared<PlayerLori>(player_id);
            break;
    }
    ch_map->push_back(player_id, player);
    std::cout << "agrego player al juego" << std::endl;
    gameMundo.addPlayer(player, spawn);
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
