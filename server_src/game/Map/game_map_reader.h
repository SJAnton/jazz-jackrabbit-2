#ifndef SERVER_GAME_MAP_READER_H_
#define SERVER_GAME_MAP_READER_H_

#include <fstream>
#include <iostream>
#include <filesystem>
#include <yaml-cpp/yaml.h>

#include "../../../common_src/tile_map.h"
#include "../GameObjects/Enemies/game_object_enemy.h"

struct Level {
    int spawn_x;
    int spawn_y;
    int tile_map_height;
    int tile_map_width;
    TileMap tile_map;
    std::vector<std::shared_ptr<ObjectEnemy>> enemies;
    std::vector<std::shared_ptr<ObjectCollected>> objects;

    Level(int spawn_x, int spawn_y, int height, int width, TileMap &tile_map,
          std::vector<std::shared_ptr<ObjectEnemy>> enemies,
          std::vector<std::shared_ptr<ObjectCollected>> objects) : 
          spawn_x(spawn_x), spawn_y(spawn_y), tile_map_height(height),
          tile_map_width(width), tile_map(tile_map), enemies(enemies), objects(objects) {};
};

class GameMapReader {
    private:
        YAML::Node node;

        std::map<std::string, std::vector<int>> &data;

        std::vector<std::string> get_levels();

        std::shared_ptr<ObjectEnemy> initialize_enemy(TipoEnemy &type);

        TipoEnemy id_to_enemy_type(int id);

        TipoRecolectable id_to_object_type(int id);

    public:
        GameMapReader(std::map<std::string, std::vector<int>> &data) : data(data) {};

        std::map<uint8_t, Level> read_levels();
};
#endif
