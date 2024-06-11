#ifndef MAP_H
#define MAP_H

#include <vector>

class Map {
    public:
        Map(int width, int height);
        bool isOccupied(int x, int y) const;
        void setOccupied(int x, int y, bool occupied);
        int getWidth() const;
        int getHeight() const;
        bool isValidCoordinate(int x, int y) const;

    private:
        int width;
        int height;
        std::vector<std::vector<bool>> grid;
};

#endif // MAP_H
