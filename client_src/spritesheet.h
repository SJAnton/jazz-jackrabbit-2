#ifndef SPRTESHEET_H
#define SPRTESHEET_H

#include "sprite_object.h"

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <exception>

//un sprite sheet es una imagen que contiene 
//los frames que conforman una animacion 
//en forma de tira o cuadricula

class SpriteSheet : public SpriteObject {
private:
    int total_frames;
    int i; //frame actual


public:
    SpriteSheet();

    //constructor
    SpriteSheet(SDL_Renderer* renderer, const std::string &pathSprite, 
                int w, int h, int cantidadFrames);

    void nextFrame();

    int getNextFrame();

    void renderizarFrame(int numeroFrame);

    //destructor
    //-~SpriteSheet();
};



#endif
