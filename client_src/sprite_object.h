#ifndef SPRITE_OBJECT_H
#define SPRITE_OBJECT_H

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <exception>


class SpriteObject
{
protected:
    int pos_x = 0;
    int pos_y = 0;
    int widthSprite = 0;
    int heightSprite = 0;

    SDL_Texture *texture;
    SDL_Rect srcRect; //para definir la región de la imagen que se va a renderizar.
    SDL_Rect destRect; //para definir la posicion y tamaño en la pantalla

    SDL_Renderer *renderer;
    
private:
    SDL_Texture* crearTexturaParaImagen(const char *path);

public:
    //recibe la direccion de la imagen y el puntero al renderer
    SpriteObject(const std::string &pathSprite, SDL_Renderer* renderer);

    //para spriteSheets
    SpriteObject(const std::string &pathSprite, SDL_Renderer* renderer, int w, int h);

    void setPosition(int x, int y);

    void renderizar();
    
//    ~SpriteObject();
};


#endif
