#include "game_map.h"

Tileset GameMap::get_tileset() {
    return tileset;
}

Point GameMap::get_spawn_point() {
    return spawn_point;
}

std::vector<Layer> GameMap::get_layers() {
    return layers;
}

std::vector<std::shared_ptr<ObjectEnemy>> GameMap::get_enemies() {
    return enemies;
}

std::vector<std::shared_ptr<ObjectCollected>> GameMap::get_objects() {
    return objects;
}

void GameMap::addObject(std::shared_ptr<ObjectCollected> &object) {
    objects.push_back(object);
}

bool GameMap::isWall(int layerIndex, int x, int y) const {
    if (layerIndex >= 0 && layerIndex < (int)layers.size()) {
        int tileId = layers[layerIndex].getTile(x, y);
        return tileset.isSolid(tileId);
    }
    return false;
}

void GameMap::createUltraFlatMap(int layerIndex, int tileId) {
    if (layerIndex < 0 || layerIndex >= (int)layers.size()) {
        return;
    }
    for (int y = 0; y < 13; ++y) {
        for (int x = 0; x < layers[layerIndex].width; ++x) {
            layers[layerIndex].setTile(x, y, tileId);
            std::cout << "Tile set at position (" << x << ", " << y << ")" << std::endl;
        }
    }
    for (int x = 0; x < layers[layerIndex].width; ++x) {
        layers[layerIndex].setTile(x, 13, 0x01);
        std::cout << "Tile set at position (" << x << ", " << 13 << ")" << std::endl;
    }
}

void GameMap::createMountainMap(int layerIndex, int tileId) {
    if (layerIndex < 0 || layerIndex >= (int)layers.size()) {
        return;
    }
    for (int y = 0; y < layers[layerIndex].height; ++y) {
        for (int x = 0; x < layers[layerIndex].width; ++x) {
            if (y < 20) {
                layers[layerIndex].setTile(x, y, tileId);
                std::cout << "Tile set at position (" << x << ", " << y << ")" << std::endl;
            } else {
                layers[layerIndex].setTile(x, y, 0x09);
                std::cout << "Tile set at position (" << x << ", " << y << ")" << std::endl;
            }
        }
    }
    setWalls(3, 20, 20, 1, 0x01);
    setWalls(6, 15, 12, 3, 0x01);
    setWalls(10, 10, 4, 5, 0x01);
}

void GameMap::createRandomMap(int layerIndex, int tileId) {
    if (layerIndex < 0 || layerIndex >= (int)layers.size()) {
        return;
    }
    for (int y = 0; y < layers[layerIndex].height; ++y) {
        for (int x = 0; x < layers[layerIndex].width; ++x) {
            if (rand() % 2 == 0) {
                layers[layerIndex].setTile(x, y, tileId);
                std::cout << "Tile set at position (" << x << ", " << y << ")" << std::endl;
            } else {
                layers[layerIndex].setTile(x, y, 0x09);
                std::cout << "Tile set at position (" << x << ", " << y << ")" << std::endl;
            }
        }
    }
}

void GameMap::createSnowyMap(int layerIndex, int tileId) {
    if (layerIndex < 0 || layerIndex >= (int)layers.size()) {
        return;
    }
    for (int y = 0; y < layers[layerIndex].height; ++y) {
        for (int x = 0; x < layers[layerIndex].width; ++x) {
            if (y < 10) {
                layers[layerIndex].setTile(x, y, tileId);
                std::cout << "Setting tile of ID " << tileId << " at position (" << x << ", " << y << ")" << std::endl;
            } else {
                layers[layerIndex].setTile(x, y, 0x09);
                std::cout << "Setting default tile (ID 0x09) at position (" << x << ", " << y << ")" << std::endl;
            }
        }
    }
    setWalls(5, 10, 15, 4, 0x02);
    setWalls(20,10, 15, 8, 0x02);
}

void GameMap::setWall(int x, int y, int tileId) {
    layers[0].setTile(x, y, tileId);
    std::cout << "Setting wall tile of ID " << tileId << " at position (" << x << ", " << y << ")" << std::endl;
}

void GameMap::setWalls(int x, int y, int width, int height, int tileId) {
    for (int i = x; i < x + width; ++i) {
        for (int j = y; j < y + height; ++j) {
            setWall(i, j, tileId);
        }
    }
}

/*
void ServerGameMap::send_map(ServerProtocol &protocol, bool &wc) {
    for (auto &layer : layers) {
        for (int y = 0; y < layer.height; ++y) {
            for (int x = 0; x < layer.width; ++x) {
                protocol.send_layer(InfoLayer(x, y, layer.getTile(x, y)), wc);
            }
        }
    }
    protocol.send_objects_size(objects.size(), wc);
    for (auto &object : objects) {
        protocol.send_objects(InfoObject(object->get_x_pos(), object->get_y_pos(),
                                            object->get_object_id()), wc);
    }
}*/
