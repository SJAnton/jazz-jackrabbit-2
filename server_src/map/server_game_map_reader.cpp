#include "server_game_map_reader.h"

#include <iostream>
#include <filesystem>

#define CURRENT_FOLDER_LENGTH 6 // "/build"
#define LEVELS_FOLDER "/levels"

#define SPAWN_POINT_KEY "SpawnPoint"
#define EXIT_POINT_KEY "ExitPoint"
#define TILE_SET_KEY "Tileset"
#define OBJECT_KEY "Objects"
#define LAYER_KEY "Layers"
#define TILE_KEY "Tile"
#define TILES_NUMBER_KEY "tiles_num"
#define TILE_MAP_KEY "tile_map"
#define IS_SOLID_KEY "is_solid"
#define X_KEY "x"
#define Y_KEY "y"
#define ID_KEY "id"
#define LAYER_HEIGHT_KEY "height"
#define LAYER_WIDTH_KEY "width"
#define OBJECT_ID_KEY "object_id"
#define AMMO_ID_KEY "ammo_id"
#define OBJECT_AMOUNT_KEY "amount"
#define OBJECT_HITBOX_KEY "hitbox"

#define AMMO_OBJECT_ID 1
#define CARROT_ID 2
#define COIN_ID 3
#define GEM_ID 4
#define POISONED_FRUIT_ID 5

// c_cpp_properties.json --> cppStandard: "c++17"
namespace fs = std::filesystem;

std::vector<std::string> ServerGameMapReader::get_levels() {
    std::vector<std::string> levels_path;

    std::string path = fs::current_path();

    path.erase(path.length() - CURRENT_FOLDER_LENGTH);
    path += LEVELS_FOLDER;

    for (auto &dir : std::filesystem::directory_iterator(path)) {
        levels_path.push_back((dir.path()));
    }
    return levels_path;
}

std::map<uint8_t, ServerGameMap> ServerGameMapReader::read_levels() {
    std::vector<std::string> levels_path = get_levels();
    std::map<uint8_t, ServerGameMap> levels;
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
        uint8_t exit_x = 0;
        uint8_t exit_y = 0;
        int tiles_num = 0;
        int layers_height = 0;
        int layers_width = 0;
        std::vector<std::vector<int>> tile_map;
        std::vector<std::shared_ptr<Object>> objects;

        for (YAML::iterator it = node.begin(); it != node.end(); ++it) {
            // Itera todas las keys
            YAML::Node key = it->first;
            YAML::Node value = it->second;

            if (key.as<std::string>() == SPAWN_POINT_KEY) {
                spawn_x = value[X_KEY].as<uint8_t>();
                spawn_y = value[Y_KEY].as<uint8_t>();

            } else if (key.as<std::string>() == EXIT_POINT_KEY) {
                exit_x = value[X_KEY].as<uint8_t>();
                exit_y = value[Y_KEY].as<uint8_t>();

            } else if (key.as<std::string>() == TILE_SET_KEY) {
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

            } else if (key.as<std::string>() == OBJECT_KEY) {
                for (YAML::const_iterator obj_it = value.begin(); obj_it != value.end(); ++obj_it) {
                    YAML::Node object = *obj_it;

                    uint8_t object_id = object[OBJECT_ID_KEY].as<uint8_t>();
                    uint8_t amount = object[OBJECT_AMOUNT_KEY].as<uint8_t>();
                    uint8_t x_pos = object[X_KEY].as<uint8_t>();
                    uint8_t y_pos = object[Y_KEY].as<uint8_t>();
                    uint8_t hitbox = object[OBJECT_HITBOX_KEY].as<uint8_t>();
                    int ammo_id = 0;

                    if (object_id == AMMO_OBJECT_ID) {
                        ammo_id = object[AMMO_ID_KEY].as<int>();
                        std::shared_ptr<Ammo> ammo = std::make_shared<Ammo>(
                            object_id, x_pos, y_pos, amount, hitbox, ammo_id
                        );
                        objects.push_back(ammo);
                    } else {
                        std::shared_ptr<Object> obj = std::make_shared<Object>(
                            object_id, x_pos, y_pos, amount, hitbox
                        );
                        objects.push_back(obj);
                    }
                }
            }
        }
        ServerGameMap level(tiles_num, spawn_x, spawn_y, exit_x, exit_y,
                            layers_height, layers_width, tile_map, objects);
        levels.emplace(level_number, level);
        level_number++;
    }
    return levels;
}