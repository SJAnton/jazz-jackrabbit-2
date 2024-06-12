#ifndef SERVER_GAME_MAP_H
#define SERVER_GAME_MAP_H

#include <vector>
#include <iostream>

#include "../server_queue.h"
#include "../server_protocol.h"
#include "../server_queue_list.h"
#include "../../common_src/info_map.h"

struct Tile {
    int id;
    bool solid;
    int pixelWidth; // Ancho en píxeles
    int pixelHeight; // Alto en píxeles
    uint8_t type; // Indica si el tile es de tierra, pasto, etc
    std::string name; 

    Tile(int id = 0, bool solid = false, int pixelWidth = 30, int pixelHeight = 30, uint8_t type = 0x9, std::string name = "")
        : id(id), solid(solid), pixelWidth(pixelWidth), pixelHeight(pixelHeight), type(type) {}
};

class Tileset {

    public:
        std::vector<Tile> tiles;

        Tileset(int numTiles) {
            tiles.resize(numTiles);
        }

        void addTile(int id, bool solid, int pixelWidth, int pixelHeight, uint8_t type, std::string name) {
            if(id >= 0 && id < (int)tiles.size()) {
                tiles[id] = Tile(id, solid, pixelWidth, pixelHeight, type, name);
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

        // Obtener el ID del tile en una posición específica
        int getTile(int x, int y) const {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                return tileMap[y][x];
            }
            return -1;  // ID de tile no válido
        }
};

struct GameObject {
    int x, y;
    //std::string type;
    uint8_t type;

    GameObject(int x, int y, const /*std::string*/ uint8_t &type) : x(x), y(y), type(type) {};
};

// Define your class for the server game map
class ServerGameMap {
    public:
        Tileset tileset;
        std::vector<Layer> layers;
        std::vector<GameObject> objects;

        ServerGameMap(int numTiles, int numLayers, int layerWidth, int layerHeight, int gameSelection)
            : tileset(numTiles) {
            for (int i = 0; i < numLayers; ++i) {
                layers.emplace_back(layerWidth, layerHeight);
            }

            tileset.addTile(0, true, 32, 32, 0x00, "Ground");  // Tile de tierra
            tileset.addTile(1, true, 32, 32, 0x01, "Grass");  // Tile de pasto
            tileset.addTile(2, true, 32, 32, 0x02, "Mountain");  // Tile de montaña
            tileset.addTile(3, true, 32, 32, 0x03, "Snow");  // Tile de nieve

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

        void addObject(int x, int y, const uint8_t &type);

        void createUltraFlatMap(int layerIndex, int tileId);

        void createMountainMap(int layerIndex, int tileId);

        void createRandomMap(int layerIndex, int tileId);

        void createSnowyMap(int layerIndex, int tileId);

        bool isWall(int layerIndex, int x, int y) const;

        void setWall(int x, int y, int tileId);

        void setWalls(int x, int y, int width, int height, int tileId);

        //void send_map(Queue<InfoMap>* sndr_q);

        void send_map(ServerProtocol &protocol, bool &wc);

    };

#endif // SERVER_GAME_MAP_H