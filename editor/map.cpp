#include "map.h"

Map::Map(int width, int height) : width(width), height(height), grid(width, std::vector<bool>(height, false)) {}

bool Map::isValidCoordinate(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool Map::isOccupied(int x, int y) const {
    return grid[x][y];
}

void Map::setOccupied(int x, int y, bool occupied) {
    grid[x][y] = occupied;
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}
