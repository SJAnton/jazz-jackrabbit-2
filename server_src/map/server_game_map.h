#ifndef SERVER_GAME_MAP_H
#define SERVER_GAME_MAP_H

#include <vector>
#include <iostream>

#include "../server_queue.h"
#include "../server_protocol.h"
#include "../server_queue_list.h"
#include "../objects/server_object.h"
#include "../../common_src/info_map.h"

#define GROUND_ID 0x00
#define GRASS_ID 0x01
#define MOUNTAIN_ID 0x02
#define SNOW_ID 0x03

struct Tile {
    int id;
    bool solid;
    int width; // Ancho en píxeles
    int height; // Alto en píxeles
    uint8_t type; // Indica si el tile es de tierra, pasto, etc

    Tile(int id = 0, bool solid = false, int width = 30, int height = 30, uint8_t type = 0x9) :
            id(id), solid(solid), width(width), height(height), type(type) {}
};

class Tileset {
    public:
        std::vector<Tile> tiles;

        Tileset(int numTiles) {
            tiles.resize(numTiles);
        }

        std::vector<Tile> get_tiles() {
            return tiles;
        }

        void addTile(int id, bool solid, int pixelWidth, int pixelHeight, uint8_t type) {
            if(id >= 0 && id < (int)tiles.size()) {
                tiles[id] = Tile(id, solid, pixelWidth, pixelHeight, type);
            }
        }

        Tile getTile(int id) const {
            if(id >= 0 && id < (int)tiles.size()) {
                return tiles[id];
            }
            return Tile(-1, false, 0, 0, 0x0);  // Tile inexistente
        }

        bool isSolid(int id) const {
            if(id >= 0 && id < (int)tiles.size()) {
                return tiles[id].solid;
            }
            return false;  // Por defecto, no sólido
        }
};

class Layer {
    public:
        int width;  // Ancho de la capa
        int height; // Alto de la capa
        std::vector<std::vector<int>> tileMap;  // Matriz bidimensional de IDs de tiles

        // Constructor
        Layer(int width, int height) : width(width), height(height) {
            // Inicializar tileMap con dimensiones height x width
            tileMap.resize(height, std::vector<int>(width, 0));
        }

        // Establecer un tile en una posición específica
        void setTile(int x, int y, int tileId) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                tileMap[y][x] = tileId;
            }
        }

        void setTileMap(std::vector<std::vector<int>> &tile_map) {
            tileMap = tile_map;
        }

        // Obtener el ID del tile en una posición específica
        int getTile(int x, int y) const {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                return tileMap[y][x];
            }
            return -1;  // ID de tile no válido
        }
};

struct Point {
    uint8_t x;
    uint8_t y;

    Point(uint8_t x, uint8_t y) : x(x), y(y) {};
};

class ServerGameMap {
    public:
        Tileset tileset;
        Point spawn_point;
        Point exit_point;
        std::vector<Layer> layers;
        std::vector<std::shared_ptr<Object>> objects;

        ServerGameMap(int numTiles, int numLayers, int layerWidth, int layerHeight,
                        int gameSelection, uint8_t spawn_x, uint8_t spawn_y, uint8_t exit_x,
                            uint8_t exit_y) : tileset(numTiles), spawn_point(spawn_x, spawn_y),
                                exit_point(exit_x, exit_y) {
        
            for (int i = 0; i < numLayers; ++i) {
                layers.emplace_back(layerWidth, layerHeight);
            }

            tileset.addTile(0, true, 32, 32, GROUND_ID);   // Tile de tierra
            tileset.addTile(1, true, 32, 32, GRASS_ID);    // Tile de pasto
            tileset.addTile(2, true, 32, 32, MOUNTAIN_ID); // Tile de montaña
            tileset.addTile(3, true, 32, 32, SNOW_ID);     // Tile de nieve

            switch (gameSelection) {
                case 0:
                    createUltraFlatMap(0, 0);
                    break;
                case 1:
                    createMountainMap(0, 2);
                    break;
                case 2:
                    createRandomMap(0, 1);
                    break;
                case 3:
                    createSnowyMap(0, 3);
                    break;
                default:
                    createUltraFlatMap(0, 0);
                    break;
            }
        }

        ServerGameMap(int numTiles, uint8_t spawn_x, uint8_t spawn_y, uint8_t exit_x,
                        uint8_t exit_y, uint8_t layers_height, uint8_t layers_width,
                            std::vector<std::vector<int>> &tile_map, 
                                std::vector<std::shared_ptr<Object>> &objects) : 
                                tileset(numTiles), spawn_point(spawn_x, spawn_y),
                                    exit_point(exit_x, exit_y), objects(objects) {
            // Crea un GameMap leído desde un archivo
            layers.emplace_back(layers_width, layers_height);
            layers[0].setTileMap(tile_map);
        }

        Tileset get_tileset();

        Point get_spawn_point();

        Point get_exit_point();

        std::vector<Layer> get_layers();

        std::vector<std::shared_ptr<Object>> get_objects();

        void addObject(std::shared_ptr<Object> &object);

        void createUltraFlatMap(int layerIndex, int tileId);

        void createMountainMap(int layerIndex, int tileId);

        void createRandomMap(int layerIndex, int tileId);

        void createSnowyMap(int layerIndex, int tileId);

        bool isWall(int layerIndex, int x, int y) const;

        void setWall(int x, int y, int tileId);

        void setWalls(int x, int y, int width, int height, int tileId);

        void send_map(ServerProtocol &protocol, bool &wc);
    };
#endif // SERVER_GAME_MAP_H
