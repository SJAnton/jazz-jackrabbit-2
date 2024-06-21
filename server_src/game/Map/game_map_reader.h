#ifndef SERVER_GAME_MAP_READER_H_
#define SERVER_GAME_MAP_READER_H_

#include <fstream>
#include <iostream>
#include <filesystem>
#include <yaml-cpp/yaml.h>

#include "game_map.h"
#include "../GameObjects/Enemies/game_object_enemy.h"

class GameMapReader {
    private:
        YAML::Node node;

        std::map<std::string, std::vector<uint8_t>> &data;

        std::vector<std::string> get_levels();

        std::shared_ptr<ObjectEnemy> initialize_enemy(TipoEnemy &type);

        TipoEnemy str_to_enemy_type(const std::string &type);

        TipoRecolectable str_to_object_type(const std::string &type);

    public:
        GameMapReader(std::map<std::string, std::vector<uint8_t>> &data) : data(data) {};

        std::map<uint8_t, GameMap> read_levels();
};
#endif
