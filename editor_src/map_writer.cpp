#include "map_writer.h"

#include <fstream>
#include <filesystem>

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
#define TYPE_KEY "type"

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

void MapWriter::save_to_YAML(GameMap &game_map, std::string &name) {
    if (!std::filesystem::exists(LEVELS_ROUTE)) {
        throw std::runtime_error("Levels directory does not exist");
    } 
    Point spawn = game_map.get_spawn_point();
    GameMapTileset tileset = game_map.get_tileset();
    std::vector<Layer> layers = game_map.get_layers();
    std::vector<std::shared_ptr<ObjectEnemy>> enemies = game_map.get_enemies();
    std::vector<std::shared_ptr<ObjectCollected>> objects = game_map.get_objects();

    YAML::Emitter out;
    std::ofstream ostr(LEVELS_ROUTE + name + FILE_EXTENSION);

    out << YAML::BeginMap;

    out << YAML::Key << SPAWN_POINT_KEY;
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << X_KEY << YAML::Value << static_cast<int>(spawn.x);
    out << YAML::Key << Y_KEY << YAML::Value << static_cast<int>(spawn.y);
    out << YAML::EndMap;

    out << YAML::Key << TILESET_KEY;
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << TILES_NUMBER_KEY << YAML::Value << tileset.get_tiles().size();
    out << YAML::EndMap;

    out << YAML::Key << LAYER_KEY;
    out << YAML::Value << YAML::BeginMap;
    for (Layer &layer : layers) {
        out << YAML::Key << LAYER_HEIGHT_KEY << YAML::Value << layer.height;
        out << YAML::Key << LAYER_WIDTH_KEY << YAML::Value << layer.width;

        std::vector<std::vector<int>> tile_map = layer.tileMap;

        out << YAML::Key << TILE_MAP_KEY;
        out << YAML::Value << YAML::BeginSeq;
        for (std::vector<int> &row : tile_map) {
            out << YAML::Flow << YAML::BeginSeq;
            for (int &tile : row) {
                out << tile;
            }
            out << YAML::EndSeq;
        }
        out << YAML::EndSeq;
    }
    out << YAML::EndMap;

    out << YAML::Key << ENEMY_KEY;
    out << YAML::Value << YAML::BeginMap;
    for (std::shared_ptr<ObjectEnemy> &enemy : enemies) {
        // El resto de datos los leo del config.yaml
        out << YAML::Key << X_KEY << YAML::Value << enemy->getPosition().x;
        out << YAML::Key << Y_KEY << YAML::Value << enemy->getPosition().y;
        out << YAML::Key << TYPE_KEY << YAML::Value << enemy_type_to_str(enemy->getTipoEnemy());
    }
    out << YAML::EndMap;

    out << YAML::Key << OBJECT_KEY;
    out << YAML::Value << YAML::BeginMap;
    for (std::shared_ptr<ObjectCollected> &object : objects) {
        out << YAML::Key << X_KEY << YAML::Value << object->getPosition().x;
        out << YAML::Key << Y_KEY << YAML::Value << object->getPosition().y;
        out << YAML::Key << TYPE_KEY << YAML::Value << object_type_to_str(object->getTipoRecolectable());
    }
    out << YAML::EndMap;

    out << YAML::EndMap;

    ostr << out.c_str();

    ostr.close();
}

void MapWriter::generate_test_flat_map() {
    GameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                     FLAT_GAME_SELECTION, SPAWN_X, SPAWN_Y);

    std::string name = FLAT_MAP_NAME;

    save_to_YAML(game_map, name);
}

void MapWriter::generate_test_mountain_map() {
    GameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                     MOUNTAIN_GAME_SELECTION, SPAWN_X, SPAWN_Y);

    std::string name = MOUNTAIN_MAP_NAME;

    save_to_YAML(game_map, name);
}

void MapWriter::generate_test_random_map() {
    GameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                     RANDOM_GAME_SELECTION, SPAWN_X, SPAWN_Y);

    std::string name = RANDOM_MAP_NAME;

    save_to_YAML(game_map, name);
}

void MapWriter::generate_test_snowy_map() {
    GameMap game_map(NUM_TILES, NUM_LAYERS, LAYER_WIDTH, LAYER_HEIGHT, 
                     SNOWY_GAME_SELECTION, SPAWN_X, SPAWN_Y);

    std::string name = SNOWY_MAP_NAME;

    save_to_YAML(game_map, name);
}

std::string MapWriter::enemy_type_to_str(const TipoEnemy &type) {
    switch (type) {
        case TipoEnemy::Bat:
            return BAT_STR;
        case TipoEnemy::Diablo:
            return DIABLO_STR;
        case TipoEnemy::Rat:
            return RAT_STR;
        default:
            throw std::runtime_error("Invalid enemy type");
    }
}

std::string MapWriter::object_type_to_str(const TipoRecolectable &type) {
    switch (type) {
        case TipoRecolectable::Moneda:
            return MONEDA_STR;
        case TipoRecolectable::Diamante:
            return DIAMANTE_STR;
        case TipoRecolectable::Zanahoria:
            return ZANAHORIA_STR;
        case TipoRecolectable::Municion:
            return MUNICION_STR;
        case TipoRecolectable::Municion1:
            return MUNICION_1_STR;
        case TipoRecolectable::Municion2:
            return MUNICION_2_STR;
        case TipoRecolectable::Municion3:
            return MUNICION_3_STR;
        case TipoRecolectable::Municion4:
            return MUNICION_4_STR;
        default:
            throw std::runtime_error("Invalid object type");
    }
} 
