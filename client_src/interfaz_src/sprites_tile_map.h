#ifndef SPRITES_TILE_MAP_H
#define SPRITES_TILE_MAP_H

#include "sprites_paths.h"
#include "sprite_object.h"
#include "../../common_src/tile_map.h"
#include "../../common_src/constantes.h"

// Esta clase funciona como una libreria. No se deben crear instancias de esta clase
class SpritesTileMap
{
private:
    static bool inicializado;
    TileMap tileMap;

    static SpriteObject tile_0;
    static SpriteObject tile_1;
    static SpriteObject tile_2;
    static SpriteObject tile_3;
    static SpriteObject tile_4;
    static SpriteObject tile_5;
    static SpriteObject tile_6;
    static SpriteObject tile_7;
    static SpriteObject tile_8;
    static SpriteObject tile_9;
    static SpriteObject tile_10;
    static SpriteObject tile_11;
    static SpriteObject tile_12;
    static SpriteObject tile_13;
    static SpriteObject tile_14;
    static SpriteObject tile_15;
    static SpriteObject tile_16;
    static SpriteObject tile_17;
    static SpriteObject tile_18;
    static SpriteObject tile_19;
    static SpriteObject tile_20;
    static SpriteObject tile_21;
    static SpriteObject tile_22;
    static SpriteObject tile_23;
    static SpriteObject tile_24;
    static SpriteObject tile_25;
    static SpriteObject tile_26;
    static SpriteObject tile_27;
    static SpriteObject tile_28;
    static SpriteObject tile_29;
    static SpriteObject tile_30;
    static SpriteObject tile_31;
    static SpriteObject tile_32;
    

    SpriteObject getTile(int id_tile);

public:
    static void init();

    SpritesTileMap(const TileMap &tileMap);

    void renderizar(const Position &posCamara);

    void setTileMap(const TileMap &tileMap);

};




#endif // SPRITES_TILE_MAP_H
