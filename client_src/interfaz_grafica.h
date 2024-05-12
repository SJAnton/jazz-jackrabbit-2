#ifndef INTERFAZ_GRAFICA_H
#define INTERFAZ_GRAFICA_H

//para poder usar estas librerias tenes que instalarlas en tu sistema.
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <exception>

#define ANCHO_WINDOW 800 // representa pixeles
#define ALTO_WINDOW 600 // representa pixeles

class InterfazGrafica
{
private:
    SDL_Window* window; // ventana emergente
    SDL_Renderer* renderer;
    bool is_running = true;
    int iteracion = 0;


private:
    SDL_Texture* crearTexturaParaImagen(const std::string &imagen_path);
    SDL_Rect crearRect(int height, int width, int x, int y);
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