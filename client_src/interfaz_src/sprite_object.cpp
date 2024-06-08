#include "sprite_object.h"
#include "interfaz_grafica.h"

Uint32 fucsia = 0xff00ff;


SDL_Texture* SpriteObject::crearTexturaParaImagen(const char *path) 
{
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
        throw std::runtime_error(std::string("Error. Falló IMG_Load(). "
                                 "Probablemente la direcion recibida no existe "
                                 "o no corresponde a una imagen valida. Path: ") + path);
    }
    SDL_SetColorKey(surface, SDL_TRUE, fucsia);
    SDL_Texture* _texture = SDL_CreateTextureFromSurface(InterfazGrafica::renderer, surface);
    SDL_FreeSurface(surface);
    if (_texture == NULL)
        throw std::runtime_error(SDL_GetError());
    
    return _texture;
}

SpriteObject::SpriteObject()
{
}

SpriteObject::SpriteObject(const std::string &pathSprite) {
    texture = crearTexturaParaImagen(pathSprite.c_str());
    SDL_QueryTexture(texture, NULL, NULL, &widthSprite, &heightSprite);//obtengo el ancho y largo
    
    srcRect = {0, 0, widthSprite, heightSprite};
    destRect = {pos_x, pos_y, widthSprite, heightSprite};
}

SpriteObject::SpriteObject(const std::string &pathSprite, int w, int h) :
    widthSprite(w), heightSprite(h)
{
    texture = crearTexturaParaImagen(pathSprite.c_str());

    srcRect = {0, 0, w, h};
    destRect = {pos_x, pos_y, w, h};
}


void SpriteObject::setArea(int width, int height) {
    widthSprite = width;
    heightSprite = height;
    destRect = {pos_x, pos_y, widthSprite, widthSprite};
}


void SpriteObject::setPosition(int x, int y) {
    pos_x = x;
    pos_y = y;
    destRect = {pos_x, pos_y, widthSprite, heightSprite};
}

void SpriteObject::renderizar() const{
    SDL_RenderCopy(InterfazGrafica::renderer, texture, &srcRect, &destRect);
}

void SpriteObject::renderizarEn(int x, int y) const {
    SDL_Rect aux = {x, y, widthSprite, heightSprite};
    SDL_RenderCopy(InterfazGrafica::renderer, texture, &srcRect, &aux);
}

void SpriteObject::renderizarCorrido(int x, int y) const {
    SDL_Rect aux = {pos_x + x, pos_y + y, widthSprite, heightSprite};
    SDL_RenderCopy(InterfazGrafica::renderer, texture, &srcRect, &aux);
}



void SpriteObject::renderizarInvertido() const{
    SDL_RenderCopyEx(InterfazGrafica::renderer, texture, &srcRect, &destRect, 0, nullptr, SDL_FLIP_HORIZONTAL);    
}

void SpriteObject::renderizarInvertidoEn(int x, int y) const{
    SDL_Rect aux = {x, y, widthSprite, heightSprite};
    SDL_RenderCopyEx(InterfazGrafica::renderer, texture, &srcRect, &aux, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

void SpriteObject::renderizarInvertidoCorrido(int x, int y) const {
    SDL_Rect aux = {pos_x + x, pos_y + y, widthSprite, heightSprite};
    SDL_RenderCopyEx(InterfazGrafica::renderer, texture, &srcRect, &aux, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

