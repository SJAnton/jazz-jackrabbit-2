#include "spritesheet.h"


SpriteSheet::SpriteSheet() :
    SpriteObject()
{
    
}
//constructor
SpriteSheet::SpriteSheet(SDL_Renderer* renderer, const std::string &pathSprite, 
                int w, int h, int cantidadFrames) :
    SpriteObject(renderer, pathSprite, w, h), 
    total_frames(cantidadFrames),
    i(0)
{
    
}

void SpriteSheet::renderizarFrame(int numeroFrame) 
{
    srcRect = { i * widthSprite, 0, widthSprite, heightSprite };
    destRect = { pos_x, pos_y, widthSprite, heightSprite };

    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
};


int SpriteSheet::getNextFrame() 
{
    i++;
    if (i > total_frames)
        i = 0;
    return i;
}
void SpriteSheet::nextFrame() 
{
    i++;
    if (i >= total_frames)
        i = 0;
    this->srcRect = { i * widthSprite, 0, widthSprite, heightSprite };
}


