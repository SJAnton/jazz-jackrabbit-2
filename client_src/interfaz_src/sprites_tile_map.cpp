#include "sprites_tile_map.h"


SpriteObject SpritesTileMap::tile_0;
SpriteObject SpritesTileMap::tile_1;
SpriteObject SpritesTileMap::tile_2;
SpriteObject SpritesTileMap::tile_3;
SpriteObject SpritesTileMap::tile_4;
SpriteObject SpritesTileMap::tile_5;
SpriteObject SpritesTileMap::tile_6;
SpriteObject SpritesTileMap::tile_7;
SpriteObject SpritesTileMap::tile_8;
SpriteObject SpritesTileMap::tile_9;
SpriteObject SpritesTileMap::tile_10;
SpriteObject SpritesTileMap::tile_11;
SpriteObject SpritesTileMap::tile_12;
SpriteObject SpritesTileMap::tile_13;
SpriteObject SpritesTileMap::tile_14;
SpriteObject SpritesTileMap::tile_15;
SpriteObject SpritesTileMap::tile_16;
SpriteObject SpritesTileMap::tile_17;
SpriteObject SpritesTileMap::tile_18;
SpriteObject SpritesTileMap::tile_19;
SpriteObject SpritesTileMap::tile_20;
SpriteObject SpritesTileMap::tile_21;
SpriteObject SpritesTileMap::tile_22;
SpriteObject SpritesTileMap::tile_23;
SpriteObject SpritesTileMap::tile_24;
SpriteObject SpritesTileMap::tile_25;
SpriteObject SpritesTileMap::tile_26;
SpriteObject SpritesTileMap::tile_27;
SpriteObject SpritesTileMap::tile_28;
SpriteObject SpritesTileMap::tile_29;
SpriteObject SpritesTileMap::tile_30;
SpriteObject SpritesTileMap::tile_31;
SpriteObject SpritesTileMap::tile_32;


bool SpritesTileMap::inicializado = false;

void SpritesTileMap::init() {
    if (!inicializado) {
        tile_0 = SpriteObject(PATH_TILE_0);
        tile_1 = SpriteObject(PATH_TILE_1);
        tile_2 = SpriteObject(PATH_TILE_2);
        tile_3 = SpriteObject(PATH_TILE_3);
        tile_4 = SpriteObject(PATH_TILE_4);
        tile_5 = SpriteObject(PATH_TILE_5);
        tile_6 = SpriteObject(PATH_TILE_6);
        tile_7 = SpriteObject(PATH_TILE_7);
        tile_8 = SpriteObject(PATH_TILE_8);
        tile_9 = SpriteObject(PATH_TILE_9);
        tile_10 = SpriteObject(PATH_TILE_10);
        tile_11 = SpriteObject(PATH_TILE_11);
        tile_12 = SpriteObject(PATH_TILE_12);
        tile_13 = SpriteObject(PATH_TILE_13);
        tile_14 = SpriteObject(PATH_TILE_14);
        tile_15 = SpriteObject(PATH_TILE_15);
        tile_20 = SpriteObject(PATH_TILE_20);
        tile_21 = SpriteObject(PATH_TILE_21);
        tile_22 = SpriteObject(PATH_TILE_22);
        tile_23 = SpriteObject(PATH_TILE_23);
        tile_24 = SpriteObject(PATH_TILE_24);
        tile_25 = SpriteObject(PATH_TILE_25);
        tile_26 = SpriteObject(PATH_TILE_26);
        tile_27 = SpriteObject(PATH_TILE_27);
        tile_28 = SpriteObject(PATH_TILE_28);
        tile_29 = SpriteObject(PATH_TILE_29);
        tile_30 = SpriteObject(PATH_TILE_30);
        tile_31 = SpriteObject(PATH_TILE_31);
        tile_32 = SpriteObject(PATH_TILE_32);

        inicializado = true;
    }
}

SpritesTileMap::SpritesTileMap(const TileMap &tileMap) : tileMap(tileMap)
{}


void SpritesTileMap::renderizar(const Position &posCamara) {
    int size = 32;
    int offset = 15; // tiles de que se ven desde el centro a los lados (15 para cada lado aprox)
    int filas = tileMap.getFilas();
    int columnas = tileMap.getColumnas();

    //Pinto por fuera de los limites del terreno de juego
    for (int i = -offset; i < 0; i++) { // filas por encima del 0
        for (int j = -offset; j < filas +offset; j++) { // columnas 
            tile_9.renderizarEn(size*j - posCamara.x, size*i - posCamara.y);
        }
    }
    for (int i = 0; i < columnas+offset; i++) { 
        for (int j = -offset; j < 0; j++) { //columnas detras del 0
            tile_9.renderizarEn(size*j - posCamara.x, size*i - posCamara.y);
        }
    }

    for (int i = columnas; i < columnas + offset; i++) { // Filas por debajo de la ultima fila
        for (int j = 0; j < filas + offset; j++) { 
            tile_9.renderizarEn(size*j - posCamara.x, size*i - posCamara.y);
        }
    }
    
    for (int i = 0; i < columnas+offset; i++) { 
        for (int j = filas; j < filas+offset; j++) { //columnas detras del 0
            tile_9.renderizarEn(size*j - posCamara.x, size*i - posCamara.y);
        }
    }

    
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) { 
            int id = tileMap.terreno[j][i].getIdTile();
            SpriteObject tile = getTile(id);
            tile.renderizarEn(size*i - posCamara.x, size*j  - posCamara.y);
        }
    }


}

void SpritesTileMap::setTileMap(const TileMap &tileMap) {
    this->tileMap = tileMap;
}

SpriteObject SpritesTileMap::getTile(int id_tile) {
    switch (id_tile)
    {
    case 0: return tile_0;
    case 1: return tile_1;
    case 2: return tile_2;
    case 3: return tile_3;
    case 4: return tile_4;
    case 5: return tile_5;
    case 6: return tile_6;
    case 7: return tile_7;
    case 8: return tile_8;
    case 9: return tile_9;
    case 10: return tile_10;
    case 11: return tile_11;
    case 12: return tile_12;
    case 13: return tile_13;
    case 14: return tile_14;
    case 15: return tile_15;
    case 20: return tile_20;
    case 21: return tile_21;
    case 22: return tile_22;
    case 23: return tile_23;
    case 24: return tile_24;
    case 25: return tile_25;
    case 26: return tile_26;
    case 27: return tile_27;
    case 28: return tile_28;
    case 29: return tile_29;
    case 30: return tile_30;
    case 31: return tile_31;
    case 32: return tile_32;
    default:
        //std::cerr << "Tile no existe" << std::endl;
        return tile_0;
    }
}

