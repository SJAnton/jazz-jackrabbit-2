#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include "../../common_src/thread.h"
#include "../music_src/music_player.h"
//#include "interfaz_grafica.h"
#include "../client_player.h"

#include "button_partida.h"
#include "button_character.h"
#include <list>
#include <map>

class InterfazGrafica; // para que se pueda compilar


class EventHandler : public Thread
{
private:
    InterfazGrafica &interfaz;
    ClientPlayer &cliente;
    MusicPlayer &effectsPlayer;

    std::map<SDL_Keycode, bool> key_state; // True si la tecla está presionada, false si no

    std::list<ButtonPartida> partidas; //Para saber en qué posicion de la pantalla estan los botones
    std::list<ButtonCharacter> personajes;
    int partidaSeleccionada = 0; // guarda el id de la partida que se seleccione

    bool &keep_running;

private:
    void manejarEventosMenu(SDL_Event &e);
    void manejarSeleccionPartida(SDL_Event &e);
    void manejarSeleccionPlayer(SDL_Event &e);
    //void manejarComandosJuego(SDL_Event &e, Direcciones &dir);
    void procesarEstadoTeclas(Direcciones &dir);
    void manejarResultadosFinales(SDL_Event &e); //No implementado

    void manejarComandosJuego(SDL_Event &e, Direcciones &dir);

public:
    EventHandler(InterfazGrafica &interfaz, ClientPlayer &clientPlayer, MusicPlayer &effectsPlayer,
    const std::list<ButtonPartida> &partidas, const std::list<ButtonCharacter> &personajes,
    bool &keep_running);

    void run() override;
};

#endif
