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
#define TYPE_KEY "type"

#define BAT_CODE "EnemyBat"
#define DIABLO_CODE "EnemyDiablo"
#define RAT_CODE "EnemyRat"

#define BAT_STR "Bat"
#define DIABLO_STR "Diablo"
#define RAT_STR "Rat"
#define MONEDA_STR "Moneda"
#define DIAMANTE_STR "Diamante"
#define ZANAHORIA_STR "Zanahoria"
#define MUNICION_STR "Municion"
#define MUNICION_1_STR "Municion1"
#define MUNICION_2_STR "Municion2"
#define MUNICION_3_STR "Municion3"
#define MUNICION_4_STR "Municion4"

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

std::map<uint8_t, GameMap> GameMapReader::read_levels() {
    std::vector<std::string> levels_path = get_levels();
    std::map<uint8_t, GameMap> levels;
    uint8_t level_number = 0;

    for (std::string level_path : levels_path) {
        // Itera todos los niveles
        std::ifstream file(level_path);
        if (!file) {
            throw std::runtime_error("Failure loading level");
        }
        YAML::Node node = YAML::Load(file);

        uint8_t spawn_x = 0;
        uint8_t spawn_y = 0;
        int tiles_num = 0;
        int layers_height = 0;
        int layers_width = 0;
        std::vector<std::vector<int>> tile_map;
        std::vector<std::shared_ptr<ObjectEnemy>> enemies;
        std::vector<std::shared_ptr<ObjectCollected>> objects;

        for (YAML::iterator it = node.begin(); it != node.end(); ++it) {
            YAML::Node key = it->first;
            YAML::Node value = it->second;

            if (key.as<std::string>() == SPAWN_POINT_KEY) {
                spawn_x = value[X_KEY].as<uint8_t>();
                spawn_y = value[Y_KEY].as<uint8_t>();

            } else if (key.as<std::string>() == TILES_NUMBER_KEY) {
                tiles_num = value[TILES_NUMBER_KEY].as<int>();

            } else if (key.as<std::string>() == LAYER_KEY) {
                layers_height = value[LAYER_HEIGHT_KEY].as<int>();
                layers_width = value[LAYER_WIDTH_KEY].as<int>();

                YAML::Node tm = value[TILE_MAP_KEY];
                tile_map.resize(layers_height, std::vector<int>(layers_width));
                for (int i = 0; i < layers_height; ++i) {
                    for (int j = 0; j < layers_width; ++j) {
                        tile_map[i][j] = tm[i][j].as<int>();
                    }
                }

            } else if (key.as<std::string>() == ENEMY_KEY) {
                for (YAML::const_iterator it = value.begin(); it != value.end(); ++it) {
                    YAML::Node enemy_node = *it;

                    uint8_t x = enemy_node[X_KEY].as<uint8_t>();
                    uint8_t y = enemy_node[Y_KEY].as<uint8_t>();
                    TipoEnemy type = str_to_enemy_type(enemy_node[TYPE_KEY].as<std::string>());

                    std::shared_ptr<ObjectEnemy> enemy = initialize_enemy(type);
                    enemy->setPosition(Coordenada(x, y));
                    enemies.push_back(enemy);
                }

            } else if (key.as<std::string>() == OBJECT_KEY) {
                for (YAML::const_iterator it = value.begin(); it != value.end(); ++it) {
                    YAML::Node object_node = *it;

                    uint8_t x = object_node[X_KEY].as<uint8_t>();
                    uint8_t y = object_node[Y_KEY].as<uint8_t>();
                    TipoRecolectable type = str_to_object_type(object_node[TYPE_KEY].as<std::string>());

                    std::shared_ptr<ObjectCollected> object = std::make_shared<ObjectCollected>(type);
                    object->setPosition(Coordenada(x, y));
                    objects.push_back(object);
                }
            }
        }
        GameMap level(
            tiles_num, spawn_x, spawn_y, layers_height,
            layers_width, tile_map, enemies, objects
        );
        levels.emplace(level_number, level);
        level_number++;
    }
    return levels;
}

std::shared_ptr<ObjectEnemy> GameMapReader::initialize_enemy(TipoEnemy &type) {
    switch (type) {
        case TipoEnemy::Bat:
            return std::make_shared<ObjectEnemy>(
                TipoEnemy::Bat, WIDTH_BAT, HEIGHT_BAT, data[BAT_CODE][0],
                data[BAT_CODE][1], data[BAT_CODE][2], data[BAT_CODE][3],
                data[BAT_CODE][4], data[BAT_CODE][5],data[BAT_CODE][6]
            );
        case TipoEnemy::Diablo:
            return std::make_shared<ObjectEnemy>(
                TipoEnemy::Diablo, WIDTH_DIABLO, HEIGHT_DIABLO, data[DIABLO_CODE][0],
                data[DIABLO_CODE][1], data[DIABLO_CODE][2], data[DIABLO_CODE][3],
                data[DIABLO_CODE][4], data[DIABLO_CODE][5],data[DIABLO_CODE][6]
            );
        case TipoEnemy::Rat:
            return std::make_shared<ObjectEnemy>(
                TipoEnemy::Rat, WIDTH_RAT, HEIGHT_RAT, data[RAT_CODE][0],
                data[RAT_CODE][1], data[RAT_CODE][2], data[RAT_CODE][3],
                data[RAT_CODE][4], data[RAT_CODE][5],data[RAT_CODE][6]
            );
        default:
            throw std::runtime_error("Invalid enemy type");
    }
}

TipoEnemy GameMapReader::str_to_enemy_type(const std::string &type) {
    if (type == BAT_STR) {
        return TipoEnemy::Bat;
    } else if (type == DIABLO_STR) {
        return TipoEnemy::Diablo;
    } else if (type == RAT_STR) {
        return TipoEnemy::Rat;
    }
    throw std::runtime_error("Invalid enemy type");
}

TipoRecolectable GameMapReader::str_to_object_type(const std::string &type) {
    if (type == MONEDA_STR) {
        return TipoRecolectable::Moneda;
    } else if (type == DIAMANTE_STR) {
        return TipoRecolectable::Diamante;
    } else if (type == ZANAHORIA_STR) {
        return TipoRecolectable::Zanahoria;
    } else if (type == MUNICION_STR) {
        return TipoRecolectable::Municion;
    } else if (type == MUNICION_1_STR) {
        return TipoRecolectable::Municion1;
    } else if (type == MUNICION_2_STR) {
        return TipoRecolectable::Municion2;
    } else if (type == MUNICION_3_STR) {
        return TipoRecolectable::Municion3;
    } else if (type == MUNICION_4_STR) {
        return TipoRecolectable::Municion4;
    }
    throw std::runtime_error("Invalid object type");
}
