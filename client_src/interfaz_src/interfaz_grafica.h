#ifndef INTERFAZ_GRAFICA_H
#define INTERFAZ_GRAFICA_H

//para poder usar estas librerias tenes que instalarlas en tu sistema.
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <exception>

#include "../../common_src/info_juego.h"
#include "../client_player.h"

#include "spritesManager.h"
#include "sprite_object.h"
#include "spritesheet.h"
#include "button_partida.h"

//#define ANCHO_WINDOW 750 // representa pixeles
//#define ALTO_WINDOW 500 // representa pixeles

#include "event_handler.h"
#include "../music_src/music_player.h"

enum EstadoInterfaz {Menu, SeleccionPartida, SeleccionPlayer, Juego, ResultadosFinales};

class InterfazGrafica
{
private:
    SDL_Window* window; // ventana emergente
    bool is_running = true;
    int iteracion = 0;
    EstadoInterfaz estado;

    EstadosPlayer estado_anterior_player = EstadosPlayer::Inactive;
    EstadosEnemy estado_anterior_enemy = EstadosEnemy::Idle;

    std::map<const InfoEnemigo*, bool> enemigo_muerto;

    //uso puntero para no tener que construirlo en la member initializer list
    SpritesManager *spritesManager;

    InfoJuego infoJuego;
    Queue<InfoJuego> &queueReceptora;

    EventHandler *eventHandler;
    int max_x = ANCHO_WINDOW; //para saber donde frenar la camara.
    int max_y = ALTO_WINDOW;

public:
    static SDL_Renderer* renderer; //para poder accederlo desde otras clases
    static SDL_Rect camara; //poscion de la camara

private:
    void renderizarMenu();
    void renderizarSeleccionPartida();
    void renderizarSeleccionPlayer();
    void renderizarTablaResultados();
    void renderizarJuego();
    void (InterfazGrafica::*renderizarPantalla)(); //Puntero a funcion renderizar
    void updateCamara(const Position &pos);
    Position posRelativaACamara(const int &x, const int &y);
    
    void efectosArma(TipoArma &arma);
    void efectosPlayer(EstadosPlayer &estado, InfoPlayer &infoPlayer);
    void efectosEnemy(EstadosEnemy &estado, InfoEnemigo &infoEnemigo);

    MusicPlayer &musicPlayer;
    MusicPlayer effectsPlayer;
public:
    InterfazGrafica(
        Queue<InfoJuego> &queueReceptora, ClientPlayer &client, MusicPlayer &musicPlayer
    );
    
    bool estaAbierta();
    void addPlayer(int id, const TipoPlayer &tipo);//temporal
    void setMapa (const TileMap &mapa);

    //void recibirInformacion();

    EstadoInterfaz getEstado() { return estado;};

    void nextEstado();

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

    void renderizarActual();

    void stop();
    void cerrarInterfaz();

    ~InterfazGrafica();
};

#endif

