#ifndef INTERFAZ_GRAFICA_H
#define INTERFAZ_GRAFICA_H

//para poder usar estas librerias tenes que instalarlas en tu sistema.
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <exception>

#include "spritesManager.h"
#include "sprite_object.h"
#include "spritesheet.h"

#define ANCHO_WINDOW 750 // representa pixeles
#define ALTO_WINDOW 500 // representa pixeles

class InterfazGrafica
{
private:
    SDL_Window* window; // ventana emergente
    SDL_Renderer* renderer;
    bool is_running = true;
    int iteracion = 0;

    SpriteSheet *player1;
    SpriteSheet player2;
    SpriteSheet player3;

    SpritesManager *spritesManager; 

    //uso puntero para no tener que construirlo en la member initializer list
public:
    InterfazGrafica();

    
    bool estaAbierta();

    void manejarEventos();

    /**
     * Actualiza la iteracion, y los sprites que correspondan.
     * Avanza al siguiente frame, modifica posiciones y 
     * los sprites que cambiaron de estado.
     * 
     * (en general va a incrementar en 1, pero 
     * puede pasar que incremente mas para evitar un 
     * desfasaje en las animaciones)
    */
    void update(int it);

    /**
     * Dibuja todos los pixeles en la pantalla
     */
    void renderizar();

    void cerrarInterfaz();

    ~InterfazGrafica();
};

#endif