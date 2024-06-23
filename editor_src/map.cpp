#include "map.h"

/*
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
*/
Map::Map(int width, int height)
    : width(width), height(height),
      grid(width, QVector<SpriteInfo>(height)),
      objectGrid(width, QVector<SpriteInfo>(height)) {}

bool Map::isValidCoordinate(int x, int y) const {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

bool Map::canPlaceSprite(int x, int y, int width, int height, bool isObject) const {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (!isValidCoordinate(x + i, y + j)) {
                return false;
            }
            if (isObject) {
                if (objectGrid[x + i][y + j].occupied) {
                    return false;
                }
            } else {
                if (grid[x + i][y + j].occupied) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Map::setSpriteOccupied(int x, int y, int width, int height, bool occupied, bool isObject, const QString& identifier, const QSize& spriteSize, int uniqueId) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (isValidCoordinate(x + i, y + j)) {
                SpriteInfo& info = isObject ? objectGrid[x + i][y + j] : grid[x + i][y + j];
                info.occupied = occupied;
                info.identifier = occupied ? identifier : "";
                info.size = occupied ? spriteSize : QSize(0, 0);  // Guardar el tamaño del sprite
                info.uniqueId = occupied ? uniqueId : -1;  // Establecer el ID único
            }
        }
    }
}

bool Map::isOccupied(int x, int y) const {
    return grid[x][y].occupied;
}

bool Map::isObjectOccupied(int x, int y) const {
    return objectGrid[x][y].occupied;
}

QString Map::getIdentifier(int x, int y, bool isObject) const {
    if (isObject) {
        return objectGrid[x][y].identifier;
    }
    return grid[x][y].identifier;
}

int Map::getUniqueId(int x, int y) const {
    return objectGrid[x][y].uniqueId;
}

QSize Map::getSpriteSize(int x, int y, bool isObject) const {
    if (isValidCoordinate(x, y)) {
        const SpriteInfo& info = isObject ? objectGrid[x][y] : grid[x][y];
        return info.size;
    }
    return QSize(0, 0);
}

SpriteInfo Map::getSpriteInfo(int x, int y, bool isObject) const {
    if (isValidCoordinate(x, y)) {
        return isObject ? objectGrid[x][y] : grid[x][y];
    }
    return SpriteInfo{false, "", QSize(0, 0), -1};
}


int Map::getRows() const { return height; }

int Map::getCols() const { return width; }

