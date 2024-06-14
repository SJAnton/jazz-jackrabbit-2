#include "server_game_map.h"

Tileset ServerGameMap::get_tileset() {
    return tileset;
}

Point ServerGameMap::get_spawn_point() {
    return spawn_point;
}

Point ServerGameMap::get_exit_point() {
    return exit_point;
}

std::vector<Layer> ServerGameMap::get_layers() {
    return layers;
}

std::vector<std::shared_ptr<Object>> ServerGameMap::get_objects() {
    return objects;
}

void ServerGameMap::addObject(std::shared_ptr<Object> &object) {
    objects.push_back(object);
}

bool ServerGameMap::isWall(int layerIndex, int x, int y) const {
    if (layerIndex >= 0 && layerIndex < (int)layers.size()) {
        int tileId = layers[layerIndex].getTile(x, y);
        return tileset.isSolid(tileId);
    }
    return false;
}

void ServerGameMap::createUltraFlatMap(int layerIndex, int tileId) {
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

void ServerGameMap::createMountainMap(int layerIndex, int tileId) {
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

void ServerGameMap::createRandomMap(int layerIndex, int tileId) {
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

void ServerGameMap::createSnowyMap(int layerIndex, int tileId) {
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

void ServerGameMap::setWall(int x, int y, int tileId) {
    layers[0].setTile(x, y, tileId);
    std::cout << "Setting wall tile of ID " << tileId << " at position (" << x << ", " << y << ")" << std::endl;
}

void ServerGameMap::setWalls(int x, int y, int width, int height, int tileId) {
    for (int i = x; i < x + width; ++i) {
        for (int j = y; j < y + height; ++j) {
            setWall(i, j, tileId);
        }
    }
}

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
}
