#include "spritesheetPlayer.h"

SpriteSheetPlayer::SpriteSheetPlayer(SDL_Renderer* renderer, const std::string &pathSprite, 
                                     int w, int h, int cantidadFrames, TipoPlayer tipoPlayer) :
    SpriteSheet(renderer,pathSprite,w, h, cantidadFrames),
    tipoPlayer(tipoPlayer)
{

}
TipoPlayer SpriteSheetPlayer::getTipo()
{
    return tipoPlayer;
}

