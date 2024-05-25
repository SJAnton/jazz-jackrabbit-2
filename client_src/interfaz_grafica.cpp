#include "interfaz_grafica.h"

#include "sprite_object.h"
#include "spritesheet.h"
#include "spritesManager.h"

SDL_Renderer* InterfazGrafica::renderer = nullptr;

//constructor
InterfazGrafica::InterfazGrafica(Queue<InfoJuego> &queueReceptora) : 
    queueReceptora(queueReceptora)
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        window = SDL_CreateWindow("Ventana del juego", SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, ANCHO_WINDOW,
                                ALTO_WINDOW, SDL_WINDOW_SHOWN);
        if (window == NULL)
            throw std::runtime_error("ERROR. Falló la creacion de SDL_Window");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
            throw std::runtime_error("ERROR. Falló la creacion del SDL_Renderer");
        
        SDL_SetRenderDrawColor(renderer,255, 255, 255, 255); // pongo fondo en blanco
        is_running = true;
    }
    else {
        is_running = false;
        throw std::runtime_error("ERROR. SDL no pudo inicializarse");
    }
    spritesManager = new SpritesManager();

    spritesManager->setEstadoPlayer(0, EstadosPlayer::Inactivo);
    spritesManager->setEstadoPlayer(1, EstadosPlayer::Caminando);
    spritesManager->setEstadoPlayer(2, EstadosPlayer::AtaqueEspecial);
}

bool InterfazGrafica::estaAbierta() {
    return is_running;
}


void InterfazGrafica::recibirInformacion() {
    //estadojuego = queueReceptora.pop()
    
}
 

void InterfazGrafica::update(int it) {
    //recibirinformacion()
    //copiar toda la informacion seteandola en el spritemanager.
    //Por ej.:
    //spritesManager->setPositionPlayer(0, estadoJuego.getPlayer(0).position)
    //spritesManager->setEstadoPlayer(0, estadoJuego.getPlayer(0).estado)

    iteracion += it;
    if (iteracion % 3 == 0) {
        spritesManager->nextFramePlayer(0);
    }
    if (iteracion % 4 == 0) {
        spritesManager->nextFramePlayer(1);
    }
    if (iteracion % 4 == 0) {
        spritesManager->nextFramePlayer(2);
    }
    
} 

void InterfazGrafica::renderizar() 
{
    SDL_RenderClear(renderer);//borra todo

    //cargar todos los pixeles (fondo, terreno, objetos, players, etc)
    //(ejemplo)
    spritesManager->renderizarFondo();
    spritesManager->renderizarPlayerEn(0, 244, 256);
    //spritesManager->renderizarPlayerEn(1, 100, 0);
    //spritesManager->renderizarPlayerEn(2, 200, 0);
    //spritesManager->renderizarPlayerEn(2, 200, 200);

    //spritesManager->playerSpaz->renderizar();
    
    
    //SDL_RenderCopy(renderer, texture, &rect, &rectPos);


    SDL_RenderPresent(renderer); // dibuja todo
}
void InterfazGrafica::stop(){
    is_running = false;
} 


void InterfazGrafica::cerrarInterfaz() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//destructor
InterfazGrafica::~InterfazGrafica()
{
    delete spritesManager;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
