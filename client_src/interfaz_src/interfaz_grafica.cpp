#include "interfaz_grafica.h"

#include "sprite_object.h"
#include "spritesheet.h"
#include "spritesManager.h"
#include "characters.h"

#include "event_handler.h"

SDL_Renderer* InterfazGrafica::renderer = nullptr;

//constructor
InterfazGrafica::InterfazGrafica(Queue<InfoJuego> &queueReceptora, ClientPlayer &client) : 
    estado(Menu),
    queueReceptora(queueReceptora),
    renderizarPantalla(&InterfazGrafica::renderizarMenu)
    //manejarEventos(&InterfazGrafica::manejarEventosMenu)
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
    spritesManager->inicializarBotonesPartidas(client.getIdPartidas());
    eventHandler  =new EventHandler(*this, client, spritesManager->getBotonesPartidas());

    eventHandler->start();
    infoJuego.addPlayer();
}

bool InterfazGrafica::estaAbierta() {
    return is_running;
}

void InterfazGrafica::recibirInformacion(){
    //cliente.recibirInformacion();
    //Proceso la informacion para actualizar la interfaz
}
 

void InterfazGrafica::update(int it) {
    if (estado != Juego)
        return;
    iteracion += it;
    
    //infoJuego = queueReceptora.pop();
    if (queueReceptora.try_pop(infoJuego)) {
        Position pos(infoJuego.players[0].pos_x, infoJuego.players[0].pos_y);
        spritesManager->updatePlayer(0, infoJuego.players[0].estado, pos);
    }
    
} 


void InterfazGrafica::flipPlayer(bool flip) {
    spritesManager->flipPlayer(0, flip);
}

void InterfazGrafica::renderizarJuego() 
{
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 1);

    SDL_RenderClear(renderer);//borra todo
    spritesManager->renderizarFondo();
    spritesManager->renderizarPlayer(0);

    SDL_RenderPresent(renderer); // dibuja todo
}

void InterfazGrafica::nextEstado() {
    switch (estado)
    {
    case Menu:
        estado = SeleccionPartida;
        renderizarPantalla = &InterfazGrafica::renderizarSeleccionPartida;
        break;
    case SeleccionPartida:
        estado = SeleccionPlayer;
        //renderizarPantalla = &InterfazGrafica::renderizarSeleccionPlayer;
        break;
    case SeleccionPlayer:
        estado = Juego;
        renderizarPantalla = &InterfazGrafica::renderizarJuego;
        break;
    case Juego:
        estado = ResultadosFinales;
        //renderizarPantalla = &InterfazGrafica::renderizarTablaResultados;
        break;
    case ResultadosFinales:
        estado = Menu;
        renderizarPantalla = &InterfazGrafica::renderizarMenu;
    default:
        break;
    }
}

void InterfazGrafica::stop(){
    is_running = false;
} 

void InterfazGrafica::renderizarActual(){
    (this->*renderizarPantalla)();
}


void InterfazGrafica::renderizarMenu(){
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 1);
    SDL_RenderClear(renderer);

    spritesManager->renderizarMenu();

    SDL_RenderPresent(renderer);
}



void InterfazGrafica::renderizarSeleccionPartida(){
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 1);
    SDL_RenderClear(renderer);

    spritesManager->renderizarBotonesPartidas();
/*    Characters fontMap = Characters();


    SDL_Surface* surface = IMG_Load("../sprites/font.png");
    SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    int cantidad_partidas = 2; //Tenemos que recibir del server esto

    for (int i = 0; i < cantidad_partidas; ++i)
    {
        int id = i + 1;
        ButtonPartida boton = ButtonPartida(id);
        boton.renderizar(renderer, fontTexture, fontMap);
        partidas.push_back(boton);
    }
    */
//    renderText(renderer, fontTexture, fontMap.charMap, "CREAR PARTIDA", 167, 400, 0.5f);  

    SDL_RenderPresent(renderer);    
}

void InterfazGrafica::cerrarInterfaz() 
{
    this->is_running = false;
    eventHandler->stop();
    eventHandler->join();
    delete eventHandler;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//destructor
InterfazGrafica::~InterfazGrafica()
{
    this->is_running = false;
    eventHandler->stop();
    eventHandler->join();
    delete eventHandler;
    delete spritesManager;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
