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

private:
    SDL_Texture* crearTexturaParaImagen(const char *path);

public:
    //constructor "descartable", no inicializa nada
    SpriteObject();
    
    explicit SpriteObject(const std::string &pathSprite);
    //recibe el puntero al renderer, la direccion de la imagen, el ancho y el alto 
    explicit SpriteObject(const std::string &pathSprite, int w, int h);

    void setArea(int width, int height);
    void setPosition(int x, int y);

    void renderizar() const;
    void renderizarEn(int x, int y) const;
    void renderizarCorrido(int x, int y) const;

    void renderizarInvertido() const;
    void renderizarInvertidoEn(int x, int y) const;
    void renderizarInvertidoCorrido(int x, int y) const;


//    ~SpriteObject();
};


#endif
