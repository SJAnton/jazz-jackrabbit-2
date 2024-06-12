#ifndef INFO_MAP_H_
#define INFO_MAP_H_

class InfoMap {
    private:
        //Tileset tileset;

        //Layer layer;

    public:
        InfoMap() {};
};

class InfoLayer {
    public:
        int x;

        int y;

        int tile;

        InfoLayer(int x, int y, int tile) : x(x), y(y), tile(tile) {};
};

class InfoObject {
    public:
        int x;

        int y;

        uint8_t type;
    
        InfoObject(int x, int y, uint8_t &type) : x(x), y(y), type(type) {};
};

#endif
