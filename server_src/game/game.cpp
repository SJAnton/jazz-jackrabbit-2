#include "game.h"

#include <iostream>

#define ID_POS 0
#define ACTION_POS 1
#define DIRECTION_POS 2

#include "../../common_src/constantes_protocolo.h"

#define PTS_DIAMANTE 20
#define PTS_MONEDA 10
#define PTS_VIDA 1
#define PTS_MUNICION 3

#define PLAYER_CODE "ObjectPlayer"
#define PROJECTILE_CODE "ObjectProjectile"
#define COLLECTED_CODE "ObjectCollected"
#define RAT_CODE "EnemyRat"

//Metodo para cargar todas las constantes del config
void Game::init(std::map<std::string, std::vector<uint8_t>> &data) {
    std::vector<uint8_t> &player_data = data[PLAYER_CODE];
    std::vector<uint8_t> &projectile_data = data[PROJECTILE_CODE];
    std::vector<uint8_t> &collected_data = data[COLLECTED_CODE];
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

    EnemyRat::init(rat_data[0], rat_data[1]);

    // TODO: implementar EnemyLizard y EnemyBat
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



void Game::execute_actions(std::vector<uint8_t> &actions) {
    //chequeo si esta saltando alguno
    for (auto &p : ch_map->getPlayers()) {

        if (p->isJumping()) {
            p->jump(Direcciones::Left);
            auxJump++;
            if (auxJump > timeJump) {
                p->set_jumping_status(false);
                auxJump = 0;
            }
//            return;
        }
    }

    if (actions.empty()) {
        return;
    }
    uint8_t player_id = actions[ID_POS];
    uint8_t action = actions[ACTION_POS];
   
    Direcciones direction = Right;
    if (actions[DIRECTION_POS] == LEFT) {
        direction = Left;
    }

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
            player->set_jumping_status(true);
            player->jump(direction);
            break;
        case ACTION_SHOOT: {
            ObjectProjectile proyectil = player->shoot(direction);
            gameMundo.addProjectile(std::move(proyectil));
            break;
        }
        //case ACTION_SPECIAL_ATTACK:
            //player->special_attack();
            //break;
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

    for (auto it = ch_map->begin(); it != ch_map->end(); it++) {
        std::shared_ptr<ObjectPlayer> &Player = it->second;

        InfoPlayer player_data = Player->getInfo();
        players_data.push_back(player_data);
    }
    for (auto enemy : enemies) {
        InfoEnemigo info = enemy.getInfo();
        enemies_data.push_back(info);
    }
    for (auto item : itemsRecolectables) {
        if (item.isCollected())
            continue;
        InfoRecolectable info = item.getInfo();
        items_data.push_back(info);
    }

    InfoJuego game_data(players_data, enemies_data, items_data, gameMundo.getInfoProyectiles());
    return game_data;
}

void Game::add_player(TipoPlayer &player_type, int player_id) {
    std::shared_ptr<ObjectPlayer> player = std::make_shared<ObjectPlayer>(player_id, player_type, Weapon(10,TipoArma::Tipo_1));
    ch_map->push_back(player_id, player);
    std::cout << "agrego player al juego" << std::endl;

    gameMundo.addPlayer(player, player->getPosition());
}

void Game::remove_player(const int &player_id) {
    ch_map->erase(player_id);
}

bool Game::is_running() {
    return _is_running;
}

