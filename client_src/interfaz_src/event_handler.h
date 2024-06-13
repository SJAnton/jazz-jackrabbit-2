#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include "../../common_src/thread.h"
//#include "interfaz_grafica.h"
#include "../client_player.h"

#include "button_partida.h"
#include "button_character.h"
#include <list>

class InterfazGrafica; // para que se pueda compilar


class EventHandler : public Thread
{
private:
    InterfazGrafica &interfaz;
    ClientPlayer &cliente;

    std::list<ButtonPartida> partidas; //Para saber en qué posicion de la pantalla estan los botones
    std::list<ButtonCharacter> personajes;
    int partidaSeleccionada = 0; // guarda el id de la partida que se seleccione

private:
    void manejarEventosMenu(SDL_Event &e);
    void manejarSeleccionPartida(SDL_Event &e);
    void manejarSeleccionPlayer(SDL_Event &e);
    void manejarComandosJuego(SDL_Event &e);
    void manejarResultadosFinales(SDL_Event &e);


public:
    EventHandler(InterfazGrafica &interfaz, ClientPlayer &clientPlayer, const std::list<ButtonPartida> &partidas, const std::list<ButtonCharacter> &personajes);

    void cargarPartidas();

    void run() override;
};

#endif
