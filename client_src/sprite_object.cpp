#include "sprite_object.h"


SDL_Texture* SpriteObject::crearTexturaParaImagen(const char *path) 
{
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
        throw std::runtime_error("Error. Falló IMG_Load(). "
                                 "Probablemente la direcion recibida no existe "
                                 "o no corresponde a una imagen valida");
    }
    Uint32 fucsia = SDL_MapRGB(surface->format, 255, 0, 255);

    SDL_SetColorKey(surface, SDL_TRUE, fucsia);
    SDL_Texture* _texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (_texture == NULL)
        throw std::runtime_error(SDL_GetError());
    
    return _texture;
}

SpriteObject::SpriteObject(const std::string &pathSprite, SDL_Renderer* renderer)
{
    this->renderer = renderer;
    texture = crearTexturaParaImagen(pathSprite.c_str());
    SDL_QueryTexture(texture, NULL, NULL, &widthSprite, &heightSprite);//obtengo el ancho y largo
}

SpriteObject::SpriteObject(const std::string &pathSprite, SDL_Renderer* renderer, int w, int h) :
    widthSprite(w), heightSprite(h), renderer(renderer)
{
    //this->renderer = renderer;
    texture = crearTexturaParaImagen(pathSprite.c_str());

    srcRect = {0, 0, w, h};
    destRect = {pos_x, pos_y, w, h};
}


void SpriteObject::setPosition(int x, int y) 
{
    pos_x = x;
    pos_y = y;
    destRect = {pos_x, pos_y, widthSprite, widthSprite};
}

void SpriteObject::renderizar()
{
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}


