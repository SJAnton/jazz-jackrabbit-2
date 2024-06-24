#include "game_map_reader.h"

#include <iostream>
#include <filesystem>

#define CURRENT_FOLDER_LENGTH 6 // "/build"
#define LEVELS_FOLDER "/game/Map/levels"

#define SPAWN_POINT_KEY "SpawnPoint"
#define EXIT_POINT_KEY "ExitPoint"
#define TILESET_KEY "Tileset"
#define ENEMY_KEY "Enemies"
#define OBJECT_KEY "Objects"
#define LAYER_KEY "Layers"
#define TILE_KEY "Tile"
#define TILE_MAP_KEY "tile_map"
#define IS_SOLID_KEY "is_solid"
#define X_KEY "x"
#define Y_KEY "y"
#define ID_KEY "id"
#define TILES_NUMBER_KEY "tiles_num"
#define LAYER_HEIGHT_KEY "height"
#define LAYER_WIDTH_KEY "width"
#define ENEMY_ID_KEY "enemy_id"
#define OBJECT_ID_KEY "object_id"

#define BAT_CODE "EnemyBat"
#define DIABLO_CODE "EnemyDiablo"
#define RAT_CODE "EnemyRat"

#define BAT_ID 1
#define DIABLO_ID 2
#define RAT_ID 3

#define COIN_ID 0
#define COIN_ID2 1
#define GEM_ID 2

// c_cpp_properties.json --> cppStandard: "c++17"
namespace fs = std::filesystem;

std::vector<std::string> GameMapReader::get_levels() {
    std::vector<std::string> levels_path;

    std::string path = fs::current_path();

    path.erase(path.length() - CURRENT_FOLDER_LENGTH);
    path += LEVELS_FOLDER;

    for (auto &dir : std::filesystem::directory_iterator(path)) {
        levels_path.push_back((dir.path()));
    }
    return levels_path;
}

std::map<uint8_t, Level> GameMapReader::read_levels() {
    std::vector<std::string> levels_path = get_levels();
    std::map<uint8_t, Level> levels;
    uint8_t level_number = 0;

    for (std::string level_path : levels_path) {
        // Itera todos los niveles
        std::ifstream file(level_path);
        if (!file) {
            throw std::runtime_error("Failure loading level");
        }
        YAML::Node node = YAML::Load(file);

        int spawn_x = 0;
        int spawn_y = 0;
        int layers_height = 0;
        int layers_width = 0;
        std::vector<std::vector<int>> matrix;
        std::vector<std::shared_ptr<ObjectEnemy>> enemies;
        std::vector<ObjectCollected> objects;
        TileMap tile_map;

        for (YAML::iterator it = node.begin(); it != node.end(); ++it) {
            YAML::Node key = it->first;
            YAML::Node value = it->second;

            if (key.as<std::string>() == SPAWN_POINT_KEY) {
                spawn_x = value[X_KEY].as<int>();
                spawn_y = value[Y_KEY].as<int>();

            } else if (key.as<std::string>() == LAYER_KEY) {
                layers_height = value[LAYER_HEIGHT_KEY].as<int>();
                layers_width = value[LAYER_WIDTH_KEY].as<int>();

                YAML::Node tm = value[TILE_MAP_KEY];
                matrix.resize(layers_height, std::vector<int>(layers_width));
                for (int i = 0; i < layers_height; ++i) {
                    for (int j = 0; j < layers_width; ++j) {
                        matrix[i][j] = tm[j][i].as<int>();
                    }
                }
                tile_map = TileMap(matrix);

            } else if (key.as<std::string>() == ENEMY_KEY) {
                for (YAML::const_iterator it = value.begin(); it != value.end(); ++it) {
                    YAML::Node enemy_node = *it;

                    int x = enemy_node[X_KEY].as<int>();
                    int y = enemy_node[Y_KEY].as<int>();
                    TipoEnemy type = id_to_enemy_type(enemy_node[ENEMY_ID_KEY].as<int>());

                    std::shared_ptr<ObjectEnemy> enemy = initialize_enemy(type);
                    enemy->setPosition(Coordenada(x, y));
                    enemies.push_back(enemy);
                }

            } else if (key.as<std::string>() == OBJECT_KEY) {
                for (YAML::const_iterator it = value.begin(); it != value.end(); ++it) {
                    YAML::Node object_node = *it;

                    int x = object_node[X_KEY].as<int>();
                    int y = object_node[Y_KEY].as<int>();
                    TipoRecolectable type = id_to_object_type(object_node[OBJECT_ID_KEY].as<int>());

                    ObjectCollected object = ObjectCollected(type);
                    object.setPosition(Coordenada(x, y));
                    objects.push_back(object);
                }
            }
        }
        Level level(spawn_x, spawn_y, layers_height, layers_width, tile_map, enemies, objects);

        levels.emplace(level_number, level);
        level_number++;
    }
    return levels;
}

std::shared_ptr<ObjectEnemy> GameMapReader::initialize_enemy(TipoEnemy &type) {
    switch (type) {
        case TipoEnemy::Bat:
            return std::make_shared<EnemyBat>(
                TipoEnemy::Bat, WIDTH_BAT, HEIGHT_BAT, data[BAT_CODE][0],
                data[BAT_CODE][1], data[BAT_CODE][2], data[BAT_CODE][3],
                data[BAT_CODE][4], data[BAT_CODE][5],data[BAT_CODE][6]
            );
        case TipoEnemy::Diablo:
            return std::make_shared<EnemyDiablo>(
                TipoEnemy::Diablo, WIDTH_DIABLO, HEIGHT_DIABLO, data[DIABLO_CODE][0],
                data[DIABLO_CODE][1], data[DIABLO_CODE][2], data[DIABLO_CODE][3],
                data[DIABLO_CODE][4], data[DIABLO_CODE][5],data[DIABLO_CODE][6]
            );
        case TipoEnemy::Rat:
            return std::make_shared<EnemyRat>(
                TipoEnemy::Rat, WIDTH_RAT, HEIGHT_RAT, data[RAT_CODE][0],
                data[RAT_CODE][1], data[RAT_CODE][2], data[RAT_CODE][3],
                data[RAT_CODE][4], data[RAT_CODE][5],data[RAT_CODE][6]
            );
        default:
            throw std::runtime_error("Invalid enemy type");
    }
}

TipoEnemy GameMapReader::id_to_enemy_type(int id) {
    switch (id) {
        case BAT_ID:
            return TipoEnemy::Bat;
        case DIABLO_ID:
            return TipoEnemy::Diablo;
        case RAT_ID:
            return TipoEnemy::Rat;
        default:
            throw std::runtime_error("Invalid enemy id");
    }
}

TipoRecolectable GameMapReader::id_to_object_type(int id) {
    switch (id) {
        case COIN_ID:
            return TipoRecolectable::Moneda;
        case COIN_ID2:
            return TipoRecolectable::Moneda;
        case GEM_ID:
            return TipoRecolectable::Diamante;
        default:
            throw std::runtime_error("Invalid object id");
    }
}
