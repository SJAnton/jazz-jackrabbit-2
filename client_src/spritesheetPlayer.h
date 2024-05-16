#ifndef SPRiTESHEET_PLAYER_H
#define SPRiTESHEET_PLAYER_H

#include "spritesheet.h"
#include "../common_src/constantes.h"

class SpriteSheetPlayer : public SpriteSheet
{
private:
    TipoPlayer tipoPlayer;

public:
    SpriteSheetPlayer(SDL_Renderer* renderer, const std::string &pathSprite, 
                      int w, int h, int cantidadFrames, TipoPlayer tipoPlayer);
    TipoPlayer getTipo();
    
};

#endif
