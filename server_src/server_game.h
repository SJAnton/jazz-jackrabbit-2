#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include "server_queue.h"
#include "server_queue_list.h"
#include "server_character_map.h"
#include "../common_src/info_juego.h"
#include "../common_src/constantes_protocolo.h"
#include "characters/server_character.h"
#include "characters/server_enemy.h"

class Game {
    private:
        static bool compare_points(std::shared_ptr<Character> &ch1, std::shared_ptr<Character> &ch2);

        void check_top_three_players(std::shared_ptr<Character> &character,
                                        std::vector<std::shared_ptr<Character>> &top_players);

    public:
        Game() {};

        std::vector<uint8_t> get_actions(std::shared_ptr<Queue<uint8_t>> &q);

        void execute_actions(std::vector<uint8_t> &actions, std::shared_ptr<CharacterMap> &ch_map,
                                std::list<std::shared_ptr<Projectile>> &projectile_list,
                                    std::map<std::string, std::vector<uint8_t>> &data_map);

        void tick(std::shared_ptr<CharacterMap> &ch_map, 
                    std::vector<std::shared_ptr<Character>> &top_players,
                        std::list<std::shared_ptr<Projectile>> &projectile_list,
                            std::list<std::shared_ptr<Enemy>> &enemy_list,
                                std::list<std::shared_ptr<Object>> &object_list);

        InfoJuego snapshot(std::shared_ptr<CharacterMap> &ch_map,
                            std::list<std::shared_ptr<Projectile>> &projectile_list,
                                std::list<std::shared_ptr<Enemy>> &enemy_list,
                                    std::list<std::shared_ptr<Object>> &object_list);

        void send_snapshot(InfoJuego &game_data, std::shared_ptr<ServerQueueList> &sndr_qs);

        void remove_character(uint8_t &player_id, std::shared_ptr<CharacterMap> &ch_map);
};
#endif
