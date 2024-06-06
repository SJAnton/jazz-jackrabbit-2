#include "event_handler.h"


#include <iostream>
#include "../common_src/constantes.h"

EventHandler::EventHandler(InterfazGrafica &interfaz, ClientPlayer &clientPlayer) :
    interfaz(interfaz),
    cliente(clientPlayer)
{
}

void EventHandler::run() {
    SDL_Event e;
    Uint32 frameStart;
    while (_keep_running) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                interfaz.stop();
                stop();
                return;
            } else if (e.type == SDL_KEYDOWN) {
                Direcciones dir = Direcciones::Right;
                switch (e.key.keysym.sym) { // Obtengo el código de cada tecla
                case SDLK_SPACE: cliente.saltar(dir); 
                    break;
                case SDLK_LEFT:
                    dir = Direcciones::Left;
                    interfaz.flipPlayer(true);
                    if (SDL_GetModState() & KMOD_LCTRL) // Se presionó Ctrl + Izquierda
                        cliente.correr(dir);
                    else 
                        cliente.caminar(dir);                
                    break;
                case SDLK_RIGHT:
                    dir = Direcciones::Right;
                    interfaz.flipPlayer(false);
                    if (SDL_GetModState() & KMOD_LCTRL) // Se presionó Ctrl + Derecha
                        cliente.correr(dir);
                    else // caminar
                        cliente.caminar(dir);
                    break;
                case SDLK_d: cliente.disparar(dir);
                    break;
                case SDLK_a: cliente.ataque_especial(dir);
                    break;
                case SDLK_ESCAPE:
                    interfaz.stop();
                    stop();
                    break;
                
                default:
                    break;
                }
            }
        }

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (1000/15 > frameTime) {
            SDL_Delay(1000/15 - frameTime); // sleep
        }
    }
}
