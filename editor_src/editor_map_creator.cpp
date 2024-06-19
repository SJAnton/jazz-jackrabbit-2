#include "editor_map_creator.h"

#include <fstream>

#define LEVELS_ROUTE "../../server_src/map/levels/"
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
#define EXIT_X 10
#define EXIT_Y 20

// Claves del YAML
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
#define ENEMY_HEALTH_KEY "health"
#define ENEMY_DAMAGE_KEY "damage"
#define ENEMY_X_HITBOX_KEY "x_hitbox"
#define ENEMY_Y_HITBOX_KEY "y_hitbox"
#define OBJECT_ID_KEY "object_id"
#define AMMO_ID_KEY "ammo_id"
#define OBJECT_AMOUNT_KEY "amount"
#define OBJECT_HITBOX_KEY "hitbox"

#define AMMO_OBJECT_ID 1

void MapCreator::save_to_YAML(ServerGameMap &game_map, std::string &name) {
    Point spawn = game_map.get_spawn_point();
    Point exit = game_map.get_exit_point();
    Tileset tileset = game_map.get_tileset();
    std::vector<Layer> layers = game_map.get_layers();
    std::vector<std::shared_ptr<Enemy>> enemies = game_map.get_enemies();
    std::vector<std::shared_ptr<Object>> objects = game_map.get_objects();

    YAML::Emitter out;
    std::ofstream ostr(LEVELS_ROUTE + name + FILE_EXTENSION);

    out << YAML::BeginMap;

    // SpawnPoint
    out << YAML::Key << SPAWN_POINT_KEY;
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << X_KEY << YAML::Value << /*YAML::Hex <<*/ static_cast<int>(spawn.x);
    out << YAML::Key << Y_KEY << YAML::Value << /*YAML::Hex <<*/ static_cast<int>(spawn.y);
    out << YAML::EndMap;

    // ExitPoint
    out << YAML::Key << EXIT_POINT_KEY;
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << X_KEY << YAML::Value << /*YAML::Hex <<*/ static_cast<int>(exit.x);
    out << YAML::Key << Y_KEY << YAML::Value << /*YAML::Hex <<*/ static_cast<int>(exit.y);
    out << YAML::EndMap;

    // TileSet
    out << YAML::Key << TILESET_KEY;
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << TILES_NUMBER_KEY << YAML::Value << tileset.get_tiles().size();
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
    }
    out << YAML::EndMap;

    // Enemies
    out << YAML::Key << ENEMY_KEY;
    out << YAML::Value << YAML::BeginMap;
    for (std::shared_ptr<Enemy> enemy : enemies) {
        out << YAML::Key << ENEMY_ID_KEY << static_cast<int>(enemy->get_enemy_id());
        out << YAML::Key << ENEMY_HEALTH_KEY << static_cast<int>(enemy->get_health());
        out << YAML::Key << ENEMY_DAMAGE_KEY << static_cast<int>(enemy->get_damage());
        out << YAML::Key << X_KEY << static_cast<int>(enemy->get_x_pos());
        out << YAML::Key << Y_KEY << static_cast<int>(enemy->get_y_pos());
        out << YAML::Key << ENEMY_X_HITBOX_KEY << static_cast<int>(enemy->get_x_hitbox());
        out << YAML::Key << ENEMY_Y_HITBOX_KEY << static_cast<int>(enemy->get_y_hitbox());
    }
    out << YAML::EndMap;

    // Objects
    out << YAML::Key << OBJECT_KEY;
    out << YAML::Value << YAML::BeginMap;
    for (std::shared_ptr<Object> object : objects) {
        uint8_t object_id = object->get_object_id();
        out << YAML::Key << OBJECT_ID_KEY << static_cast<int>(object_id);

        if (object_id == AMMO_OBJECT_ID) {
            std::shared_ptr<Ammo> ammo = std::dynamic_pointer_cast<Ammo>(object);
            if (ammo != nullptr) {
                out << YAML::Key << AMMO_ID_KEY << static_cast<int>(ammo->get_id());
            }
        }
        out << YAML::Key << OBJECT_AMOUNT_KEY << static_cast<int>(object->get_amount());
        out << YAML::Key << X_KEY << static_cast<int>(object->get_x_pos());
        out << YAML::Key << Y_KEY << static_cast<int>(object->get_y_pos());
        out << YAML::Key << OBJECT_HITBOX_KEY << static_cast<int>(object->get_hitbox());
    }
    out << YAML::EndMap;

    out << YAML::EndMap;

    ostr << out.c_str();

    ostr.close();
}

void MapCreator::generate_test_flat_map() {
    ServerGameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                            FLAT_GAME_SELECTION, SPAWN_X, SPAWN_Y, EXIT_X, EXIT_Y);

    std::string name = FLAT_MAP_NAME;

    save_to_YAML(game_map, name);
}

void MapCreator::generate_test_mountain_map() {
    ServerGameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                            MOUNTAIN_GAME_SELECTION, SPAWN_X, SPAWN_Y, EXIT_X, EXIT_Y);

    std::string name = MOUNTAIN_MAP_NAME;

    save_to_YAML(game_map, name);
}

void MapCreator::generate_test_random_map() {
    ServerGameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                            RANDOM_GAME_SELECTION, SPAWN_X, SPAWN_Y, EXIT_X, EXIT_Y);

    std::string name = RANDOM_MAP_NAME;

    save_to_YAML(game_map, name);
}

void MapCreator::generate_test_snowy_map() {
    ServerGameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                            SNOWY_GAME_SELECTION, SPAWN_X, SPAWN_Y, EXIT_X, EXIT_Y);

    std::string name = SNOWY_MAP_NAME;

    save_to_YAML(game_map, name);
}
