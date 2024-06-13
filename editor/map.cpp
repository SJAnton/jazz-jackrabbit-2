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

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}
