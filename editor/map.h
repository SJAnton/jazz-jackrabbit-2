#ifndef MAP_H
#define MAP_H

#include <vector>

class Map {
    public:
        Map(int width, int height);
        bool isOccupied(int x, int y) const;
        bool isObjectOccupied(int x, int y) const;
        void setOccupied(int x, int y, bool occupied);
        void setObjectOccupied(int x, int y, bool occupied);
        int getWidth() const;
        int getHeight() const;
        bool isValidCoordinate(int x, int y) const;

        bool canPlaceSprite(int x, int y, int width, int height, bool isObject = false) const;
        void setSpriteOccupied(int x, int y, int width, int height, bool occupied, bool isObject = false);

    private:
        int width;
        int height;
        std::vector<std::vector<bool>> terrainGrid;
        std::vector<std::vector<bool>> objectGrid;
};

#endif // MAP_H
