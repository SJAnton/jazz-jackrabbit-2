#include "spritesheetPlayer.h"

SpriteSheetPlayer::SpriteSheetPlayer(const std::string &pathSprite, 
                                     int w, int h, int cantidadFrames, TipoPlayer tipoPlayer) :
    SpriteSheet(pathSprite,w, h, cantidadFrames),
    tipoPlayer(tipoPlayer)
{

}
TipoPlayer SpriteSheetPlayer::getTipo()
{
    return tipoPlayer;
}


