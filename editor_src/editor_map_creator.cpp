#include "editor_map_creator.h"

#include <fstream>

#define LEVELS_ROUTE "../../server_src/levels/"
#define FILE_EXTENSION ".yaml"

// Tests
#define FLAT_MAP_NAME "flat_test"
#define MOUNTAIN_MAP_NAME "mountain_test"
#define RANDOM_MAP_NAME "random_test"
#define SNOWY_MAP_NAME "snowy_test"
#define FLAT_GAME_SELECTION 0
#define MOUNTAIN_GAME_SELECTION 1
#define RANDOM_GAME_SELECTION 2
#define SNOWY_GAME_SELECTION 3
#define NUM_TILES 30
#define NUM_LAYERS 1
#define LAYER_WIDTH 30
#define LAYER_HEIGHT 30
#define SPAWN_X 5
#define SPAWN_Y 20

// Claves del YAML
#define SPAWN_POINT_KEY "SpawnPoint"
#define OBJECT_KEY "Objects"
#define LAYER_KEY "Layers"
#define TILE_KEY "Tile"
#define TILE_MAP_KEY "tile_map"
#define IS_SOLID_KEY "is_solid"
#define X_KEY "x"
#define Y_KEY "y"
#define ID_KEY "id"
#define LAYER_HEIGHT_KEY "height"
#define LAYER_WIDTH_KEY "width"
#define OBJECT_ID_KEY "object_id"

void MapCreator::save_to_YAML(ServerGameMap &game_map, std::string &name) {
    SpawnPoint spawn = game_map.get_spawn_point();
    std::vector<Layer> layers = game_map.get_layers();
    std::vector<Tile> tiles = game_map.get_tileset().get_tiles();
    std::vector<std::shared_ptr<Object>> objects = game_map.get_objects();

    YAML::Emitter out;
    std::ofstream ostr(LEVELS_ROUTE + name + FILE_EXTENSION);

    out << YAML::BeginMap; // Inicio escritura

    // SpawnPoint
    out << YAML::Key << SPAWN_POINT_KEY;
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << X_KEY << YAML::Value << YAML::Hex << spawn.x;
    out << YAML::Key << Y_KEY << YAML::Value << YAML::Hex << spawn.y;
    out << YAML::EndMap;

    // Layers
    out << YAML::Key << LAYER_KEY;
    out << YAML::Value << YAML::BeginMap;
    for (Layer layer : layers) {
        out << YAML::Key << LAYER_HEIGHT_KEY << YAML::Value << layer.height;
        out << YAML::Key << LAYER_WIDTH_KEY << YAML::Value << layer.width;

        std::vector<std::vector<int>> tile_map = layer.tileMap;

        // TileMap
        out << YAML::Key << TILE_MAP_KEY;
        out << YAML::Value << YAML::BeginSeq;
        for (std::vector<int> row : tile_map) {
            out << YAML::Flow << YAML::BeginSeq;
            for (int tile : row) {
                out << tile;
            }
            out << YAML::EndSeq;
        }
        out << YAML::EndSeq;

        // IsSolid
        out << YAML::Key << IS_SOLID_KEY;
        out << YAML::Value << YAML::BeginSeq;
        int tm_size = tile_map.size();
        for (int x = 0; x < tm_size; ++x) {
            out << YAML::Flow << YAML::BeginSeq;
            for (size_t y = 0; y < tile_map[x].size(); ++y) {
                game_map.get_tileset().get_tiles();
            }
            out << YAML::EndSeq;
        }
        out << YAML::EndSeq;
    }
    out << YAML::EndMap;

    // Objects
    out << YAML::Key << OBJECT_KEY;
    out << YAML::Value << YAML::BeginMap;
    for (std::shared_ptr<Object> object : objects) {
        out << YAML::Key << OBJECT_ID_KEY << object->get_object_id();
        out << YAML::Key << X_KEY << object->get_x_pos();
        out << YAML::Key << Y_KEY << object->get_y_pos();
    }
    out << YAML::EndMap;

    out << YAML::EndMap; // Fin escritura

    ostr << out.c_str();

    ostr.close();
}

void MapCreator::generate_test_flat_map() {
    ServerGameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                            FLAT_GAME_SELECTION, SPAWN_X, SPAWN_Y);

    std::string name = FLAT_MAP_NAME;

    save_to_YAML(game_map, name);
}

void MapCreator::generate_test_mountain_map() {
    ServerGameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                            MOUNTAIN_GAME_SELECTION, SPAWN_X, SPAWN_Y);

    std::string name = MOUNTAIN_MAP_NAME;

    save_to_YAML(game_map, name);
}

void MapCreator::generate_test_random_map() {
    ServerGameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                            RANDOM_GAME_SELECTION, SPAWN_X, SPAWN_Y);

    std::string name = RANDOM_MAP_NAME;

    save_to_YAML(game_map, name);
}

void MapCreator::generate_test_snowy_map() {
    ServerGameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                            SNOWY_GAME_SELECTION, SPAWN_X, SPAWN_Y);

    std::string name = SNOWY_MAP_NAME;

    save_to_YAML(game_map, name);
}
