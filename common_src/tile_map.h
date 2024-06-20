#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <vector>
#include <cstdint>

#define ID_FONDO_1 2
#define ID_FONDO_2 3
class Tile {
    private:
        int id_tile; // ver en sprites de terreno las posiilidades (del 1 al ...) (Agregar mas)
        bool is_solid; // para el server
    
    Tile (int id_tile) : id_tile(id_tile){
        if (id_tile != ID_FONDO_1 && id_tile != ID_FONDO_2)
            is_solid = true;
        else 
            is_solid = false;
    }
};

class TileMap
{
public:
    std::vector<std::vector<Tile>> terreno; // matriz de tiles


    // Constructor a partir de 
    TileMap(std::vector<std::vector<int>> matriz_ids_tiles);

    //Constructor a partir de bytes
    TileMap(std::vector<uint8_t> matriz_ids_tiles);


    std::vector<uint8_t> toBytes();
};


#endif //TILE__MAP_H
