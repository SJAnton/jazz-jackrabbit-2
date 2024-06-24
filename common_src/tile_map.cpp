#include "tile_map.h"

#include <iostream>

 int level_1[30][30] = {
        {9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 12, 12, 12, 12, 12, 12, 12, 12, 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 0 , 12, 12, 12, 12, 12, 13, 13, 13, 6 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 10, 6 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 10, 6 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 10, 13, 13, 13, 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 13, 13, 9 },
        {9 , 2 , 2 , 0 , 13, 12, 12, 12, 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 0 , 12, 12, 12, 12, 12, 12, 12, 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 0 , 12, 12, 12, 12, 12, 12, 12, 1 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 9 },
        {9 , 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9 },
        {9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 },  
    };


TileMap::TileMap(std::vector<std::vector<int>> matriz_ids_tiles) {
    int size = matriz_ids_tiles.size();
    
    for (int i = 0; i < size; ++i) {
        std::vector<Tile> fila;
        int columnas = matriz_ids_tiles[i].size();
        for (int j = 0; j < columnas; ++j) {
            fila.push_back(Tile(matriz_ids_tiles[j][i]));
        }
        terreno.push_back(fila);
    }
}

TileMap::TileMap(std::vector<uint8_t> matriz_ids_tiles) {
    if (matriz_ids_tiles.size() < 2) {
        throw std::runtime_error("Invalid input: not enough data for dimensions.");
    }

    int columnas = matriz_ids_tiles[0];
    int filas = matriz_ids_tiles[1];


  //  if (matriz_ids_tiles.size() < (2 + filas * columnas)) {
    //    throw std::runtime_error("Invalid input: not enough data for the specified dimensions.");
    //}

    int index = 2; // Start after the first two bytes (columns and rows)

    for (int i = 0; i < filas; ++i) {
        std::vector<Tile> fila;
        for (int j = 0; j < columnas; ++j) {
            fila.push_back(Tile(matriz_ids_tiles[index]));
            ++index;
        }
        terreno.push_back(fila);
    }
   /*
    std::cout << "filas cargadas: " << terreno.size() <<  std::endl;
    std::cout << "Columnas cargadas: " << terreno[0].size() <<  std::endl;

    std::cout << "tilemap creado: " << std::endl;
    for (const auto& fila : terreno) {
        for (const auto& tile : fila) {
            std::cout << tile.getIdTile() << " ";
        }
        std::cout << std::endl;
    }
    */
    
}


std::vector<uint8_t> TileMap::toBytes() {
    std::vector<uint8_t> bytes;
    bytes.push_back(terreno.size()); //filas
    bytes.push_back(terreno[0].size()); //columnas

    for (int i = 0; i < (int)terreno.size(); ++i) {
        for (int j = 0; j < (int)terreno[i].size(); ++j) {
            bytes.push_back((uint8_t)terreno[i][j].getIdTile());
        }
    }
    return bytes;
}

TileMap TileMap::getLevel_1() {
    std::vector<std::vector<int>> matriz_ids_tiles;
    for (int i = 0; i < 30; ++i) {
        std::vector<int> fila;
        for (int j = 0; j < 30; ++j) {
            fila.push_back(level_1[j][i]);
        }
        matriz_ids_tiles.push_back(fila);
    }
    return TileMap(matriz_ids_tiles);
}

