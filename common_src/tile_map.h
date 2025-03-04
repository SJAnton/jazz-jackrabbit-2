#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <vector>
#include <cstdint>

#define ID_FONDO_1 2
#define ID_FONDO_2 3
#define ID_FONDO_3 26
#define ID_FONDO_4 27
#define ID_FONDO_5 28

class Tile {
    private:
        int id_tile; // ver en sprites de terreno las posibilidades (del 1 al 15)
        bool _is_solid; // para el server
    
    public:
        Tile (const int &id_tile) : id_tile(id_tile) {
            if (id_tile == ID_FONDO_1 || id_tile == ID_FONDO_2 || id_tile == ID_FONDO_3 || id_tile == ID_FONDO_4 || id_tile == ID_FONDO_5)
                _is_solid = false;
            else 
                _is_solid = true;
        };

        bool is_solid() const {return _is_solid;};
        int getIdTile() const {return id_tile;};
};

class TileMap
{
public:
    std::vector<std::vector<Tile>> terreno; // matriz de tiles


    // Constructor a partir de una matriz de id's de tiles
    TileMap(std::vector<std::vector<int>> matriz_ids_tiles);

    TileMap() {};

    /**
     * Constructor a partir de una tira de bytes, donde 
     * el primer byte indica la cantidad de columnas y el segundo la cantidad de fiilas
    */
    explicit TileMap(std::vector<uint8_t> matriz_ids_tiles);


    /**
     * Serializa el tilemap en una tira de bytes
    */
    std::vector<uint8_t> toBytes();

    static TileMap getLevel_1();

    int getFilas() const {return terreno[0].size();};
    int getColumnas() const {return terreno.size();};
};


#endif //TILE__MAP_H
