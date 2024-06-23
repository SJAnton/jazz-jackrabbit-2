#ifndef MAP_H
#define MAP_H

#include <vector>
#include <QString>
#include <QVector>
#include <QSize>
/*
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
*/
struct SpriteInfo {
    bool occupied = false;
    QString identifier = "";
    QSize size = QSize(0, 0);
    int uniqueId = -1;

    SpriteInfo(bool occ = false, const QString& id = "", const QSize& sz = QSize(0, 0), int uid = -1)
        : occupied(occ), identifier(id), size(sz), uniqueId(uid) {}
};

class Map {
public:
    Map(int width, int height);

    bool isValidCoordinate(int x, int y) const;
    bool canPlaceSprite(int x, int y, int width, int height, bool isObject) const;
    void setSpriteOccupied(int x, int y, int width, int height, bool occupied, bool isObject, const QString& identifier = "", const QSize& spriteSize = QSize(0, 0), int uniqueId = -1);
    bool isOccupied(int x, int y) const;
    bool isObjectOccupied(int x, int y) const;
    QString getIdentifier(int x, int y, bool isObject) const;
    QSize getSpriteSize(int x, int y, bool isObject) const;
    SpriteInfo getSpriteInfo(int x, int y, bool isObject) const;
    int getRows() const;
    int getCols() const;
    int getUniqueId(int x, int y) const;


private:
    QVector<QVector<SpriteInfo>> grid;
    QVector<QVector<SpriteInfo>> objectGrid;
    int width;
    int height;
};


#endif // MAP_H
