#include "interfaz_grafica.h"

#include "sprite_object.h"
#include "spritesheet.h"
#include "spritesManager.h"
#include "characters.h"

#include "event_handler.h"

SDL_Renderer* InterfazGrafica::renderer = nullptr;

SDL_Rect InterfazGrafica::camara = {0,0,ANCHO_WINDOW, ALTO_WINDOW};

//constructor
InterfazGrafica::InterfazGrafica(Queue<InfoJuego> &queueReceptora, ClientPlayer &client) : 
    estado(Menu),
    queueReceptora(queueReceptora),
    renderizarPantalla(&InterfazGrafica::renderizarMenu)
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
    spritesManager->inicializarBotonesCharacter();
    eventHandler =  new EventHandler(*this, client, spritesManager->getBotonesPartidas(), spritesManager->getBotonesCharacter());

    eventHandler->start();
    //infoJuego.addPlayer();
}

bool InterfazGrafica::estaAbierta() {
    return is_running;
}

void InterfazGrafica::recibirInformacion(){
    //cliente.recibirInformacion();
    //Proceso la informacion para actualizar la interfaz
}
 
void InterfazGrafica::addPlayer(const TipoPlayer &tipo) {//temporal
    spritesManager->addPlayer(tipo);
}
//muevo la camara para que quede centrada en la posicion recibida
void InterfazGrafica::updateCamara(const Position &pos) {
    
    camara.x = pos.x - ANCHO_WINDOW/2;
    camara.y = pos.y - ALTO_WINDOW/2;
}

void InterfazGrafica::update(int it) {
    if (estado != Juego)
        return;
    iteracion += it;
    
    //infoJuego = queueReceptora.pop();
    if (queueReceptora.try_pop(infoJuego)) {
        Position pos(infoJuego.players[0].pos_x, infoJuego.players[0].pos_y); //el player 0 debo "ser yo"
        updateCamara(pos);
        
        for (int i=0; i< infoJuego.cantidadPlayers(); i++) {
            pos = posRelativaACamara(infoJuego.players[i].pos_x, infoJuego.players[i].pos_y);
            spritesManager->updatePlayer(i, infoJuego.players[i].estado, pos);
        }
        for (int i=0; i< infoJuego.cantEnemigos(); i++) {
            pos = posRelativaACamara(infoJuego.enemigos[i].pos_x, infoJuego.enemigos[i].pos_y);
            //spritesManager->updateEnemy(i, infoJuego.enemigos[i].estado, pos);
        }
    }

    if (iteracion % 2 == 0)
        spritesManager->updateItems();

    spritesManager->updateProyectiles();
} 


void InterfazGrafica::flipPlayer(bool flip) {
    spritesManager->flipPlayer(0, flip);
}

Position InterfazGrafica::posRelativaACamara(const int &x, const int &y) {
    return Position(x - camara.x, y- camara.y);
}

void InterfazGrafica::renderizarJuego() 
{
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 1);

    SDL_RenderClear(renderer);//borra todo
    spritesManager->renderizarFondo(Position(camara.x, camara.y));

    for (int i=0; i< infoJuego.cantidadPlayers(); i++) {
        spritesManager->renderizarPlayer(i);
    }

    for (int i=0; i< infoJuego.cantEnemigos(); i++) {
        //spritesManager->renderizarEnemigo(i);
    }

    //renderizo los items
    for (int i=0; i< infoJuego.cantRecolectables(); i++) {
        Position pos = posRelativaACamara(infoJuego.recolectables[i].pos_x, infoJuego.recolectables[i].pos_y);
        spritesManager->renderizarItemEn(infoJuego.recolectables[i].tipo, pos.x, pos.y);
    }

    //renderizo los proyectiles
    for (int i=0; i< infoJuego.cantProyectiles(); i++) {
        //std::cout << "Hay " << infoJuego.cantProyectiles() << " proyectiles" << std::endl;
        Position pos = posRelativaACamara(infoJuego.proyectiles[i].pos_x, infoJuego.proyectiles[i].pos_y);
        spritesManager->renderizarProyectilEn(infoJuego.proyectiles[i].direccion, pos.x, pos.y);
        //spritesManager->updatePlayer(i, infoJuego.players[i].estado, posicion);
    }

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
        renderizarPantalla = &InterfazGrafica::renderizarSeleccionPlayer;
        break;
    case SeleccionPlayer:
        estado = Juego;
        renderizarPantalla = &InterfazGrafica::renderizarJuego;
        break;
    case Juego:
        estado = ResultadosFinales; //no implementado
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
    SDL_SetRenderDrawColor(renderer,106, 101, 255, 1);
    SDL_RenderClear(renderer);

    spritesManager->renderizarBotonesPartidas(); 

    SDL_RenderPresent(renderer);    
}

void InterfazGrafica::renderizarSeleccionPlayer(){
    SDL_SetRenderDrawColor(renderer,106, 101, 255, 1);
    SDL_RenderClear(renderer);

    spritesManager->renderizarBotonesCharacter();

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
