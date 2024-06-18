#include "map.h"

Map::Map(int width, int height)
    : width(width), height(height),
      terrainGrid(width, std::vector<bool>(height, false)),
      objectGrid(width, std::vector<bool>(height, false)) {}

bool Map::isValidCoordinate(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool Map::isOccupied(int x, int y) const {
    return terrainGrid[x][y];
}

bool Map::isObjectOccupied(int x, int y) const {  // Nueva función
    return objectGrid[x][y];
}

void Map::setOccupied(int x, int y, bool occupied) {
    terrainGrid[x][y] = occupied;
}

void Map::setObjectOccupied(int x, int y, bool occupied) {  // Nueva función
    if (isValidCoordinate(x, y)) {
        objectGrid[x][y] = occupied;
    }
}
/*
bool Map::canPlaceSprite(int x, int y, int width, int height, bool isObject) const {
    for (int i = x; i < x + width; ++i) {
        for (int j = y; j < y + height; ++j) {
            if (!isValidCoordinate(i, j) || (isObject ? isObjectOccupied(i, j) : isOccupied(i, j))) {
                return false;
            }
        }
    }
    return true;
}
*/

bool Map::canPlaceSprite(int x, int y, int width, int height, bool isObject) const {
    for (int i = x; i < x + width; ++i) {
        for (int j = y; j < y + height; ++j) {
            if (!isValidCoordinate(i, j) || (isObject ? objectGrid[i][j] : terrainGrid[i][j])) {
                return false;
            }
        }
    }
    return true;
}


void Map::setSpriteOccupied(int x, int y, int width, int height, bool occupied, bool isObject) {
    for (int i = x; i < x + width; ++i) {
        for (int j = y; j < y + height; ++j) {
            if (isObject) {
                objectGrid[i][j] = occupied;
            } else {
                terrainGrid[i][j] = occupied;
            }
        }
    }
}



int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}
