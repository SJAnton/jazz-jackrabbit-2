#ifndef INTERFAZ_GRAFICA_H
#define INTERFAZ_GRAFICA_H

//para poder usar estas librerias tenes que instalarlas en tu sistema.
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <exception>
#include "client_player.h"

#include "spritesManager.h"
#include "sprite_object.h"
#include "spritesheet.h"
#include "client_player.h"
#include "../common_src/info_juego.h"

#define ANCHO_WINDOW 750 // representa pixeles
#define ALTO_WINDOW 500 // representa pixeles

class InterfazGrafica
{
private:
    SDL_Window* window; // ventana emergente
    bool is_running = true;
<<<<<<< HEAD
    int iteracion = 0;    
=======
    bool menu_abierto = true;
    int iteracion = 0;
    
    ClientPlayer cliente;//
>>>>>>> af8ff760c996947a6dd2a5a503acca45914e0aee
    //uso puntero para no tener que construirlo en la member initializer list
    SpritesManager *spritesManager;

    Queue<InfoJuego> &queueReceptora;

public:
    static SDL_Renderer* renderer; //para poder accederlo desde otras clases

public:
    InterfazGrafica(Queue<InfoJuego> &queueReceptora);
    
    bool estaAbierta();

    bool menuAbierto();

    void manejarEventos();

    void manejarEventosMenu();

    void recibirInformacion();

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
<<<<<<< HEAD
    void stop();
=======

    void renderizarMenu();

>>>>>>> af8ff760c996947a6dd2a5a503acca45914e0aee
    void cerrarInterfaz();

    ~InterfazGrafica();
};

#endif