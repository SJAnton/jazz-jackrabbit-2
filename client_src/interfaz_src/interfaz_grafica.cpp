#include "interfaz_grafica.h"
#include "sprite_object.h"
#include "spritesheet.h"
#include "spritesManager.h"
#include "characters.h"
#include "event_handler.h"

#define MENU_MUSIC_PATH "../music_src/Music/TitleScreen.mp3"
#define SELECTION_MUSIC_PATH "../music_src/Music/Selection.mp3"
#define CASTLE_MUSIC_PATH "../music_src/Music/Castle.mp3"
#define COLONIUS_MUSIC_PATH "../music_src/Music/Colonius.mp3"
#define LABRATORY_MUSIC_PATH "../music_src/Music/Labratory.mp3"
#define MEDIVO_MUSIC_PATH "../music_src/Music/Medivo.mp3"

#define EFFECTS_VOLUME 100

#define SHOOTING_EFFECT_PATH "../music_src/Effects/Shooting.mp3"

SDL_Renderer* InterfazGrafica::renderer = nullptr;

SDL_Rect InterfazGrafica::camara = {0,0,ANCHO_WINDOW, ALTO_WINDOW};

//constructor
InterfazGrafica::InterfazGrafica(
    Queue<InfoJuego> &queueReceptora, ClientPlayer &client, MusicPlayer &musicPlayer
    ) : estado(Menu),
        queueReceptora(queueReceptora),
        renderizarPantalla(&InterfazGrafica::renderizarMenu),
        musicPlayer(musicPlayer),
        effectsPlayer(EFFECTS_VOLUME)
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

void InterfazGrafica::addPlayer(const TipoPlayer &tipo) {//temporal
    spritesManager->addPlayer(tipo);
}

void InterfazGrafica::setMapa (const TileMap &mapa) {
    spritesManager->setMapa(mapa);
}

//muevo la camara para que quede centrada en la posicion recibida
void InterfazGrafica::updateCamara(const Position &pos) {
    
    camara.x = pos.x - ANCHO_WINDOW/2;
    camara.y = pos.y - ALTO_WINDOW/2;
}
Position InterfazGrafica::posRelativaACamara(const int &x, const int &y) {
    return Position(x - camara.x, y- camara.y);
}

void InterfazGrafica::update(int it) {
    if (estado != Juego)
        return;
    iteracion += it;
    
    try {
        infoJuego = queueReceptora.pop();
    } catch (const ClosedQueue& e) {
        std::cout << "cierro interfaz en update()" << std::endl;
        cerrarInterfaz();
    }
        Position pos(infoJuego.players[0].pos_x, infoJuego.players[0].pos_y); // el player 0 debo "ser yo"
        updateCamara(pos);
        //std::cout << "Cant players: " << infoJuego.cantidadPlayers() << std::endl;

        for (int i=0; i< infoJuego.cantidadPlayers(); i++) {
            pos = posRelativaACamara(infoJuego.players[i].pos_x, infoJuego.players[i].pos_y);
            try {

                EstadosPlayer estado = infoJuego.players[i].estado;

                /*switch (estado) {
                    case EstadosPlayer::Shooting:
                        effectsPlayer.play_effect(SHOOTING_EFFECT_PATH);
                        break;
                    default:
                        break;
                }*/

                spritesManager->updatePlayer(i, estado, pos, infoJuego.players[i].direccion);
            } catch (...) { // si lanza una excepcion quiere decir que el player i no existe en spritesManager. Debo agregarlo
                spritesManager->addPlayer(infoJuego.players[i].tipoPlayer);
                spritesManager->updatePlayer(i, infoJuego.players[i].estado, pos, infoJuego.players[i].direccion);
            }
            
        }
        for (int i=0; i< infoJuego.cantEnemigos(); i++) {
            pos = posRelativaACamara(infoJuego.enemigos[i].pos_x, infoJuego.enemigos[i].pos_y);
            try {
                spritesManager->updateEnemy(i, infoJuego.enemigos[i].estado, pos, infoJuego.enemigos[i].direccion);
            } catch (...) {
                if (infoJuego.enemigos[i].tipo == Bat)
                    std::cout << "agrego un bat" << std::endl;
                spritesManager->addEnemy(infoJuego.enemigos[i].tipo);
                spritesManager->updateEnemy(i, infoJuego.enemigos[i].estado, pos, infoJuego.enemigos[i].direccion);
            }
            
        }
    

    if (iteracion % 2 == 0) {
        spritesManager->updateItems();
        spritesManager->updateProyectiles();
    }

} 

void InterfazGrafica::renderizarJuego() 
{
    if (!is_running)
        return;
    if (infoJuego.cantidadPlayers() == 0) {
        throw std::runtime_error("No hay ningun Player cargardo aun. En InterfazGrafica::renderizarJuego()");
    }
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 1);
    SDL_RenderClear(renderer);//borra todo

    spritesManager->renderizarTerreno(Position(camara.x, camara.y));

    // renderizo players
    for (int i=0; i< infoJuego.cantidadPlayers(); i++) {
        spritesManager->renderizarPlayer(i);
    }
    //renderizo enemigos
    for (int i=0; i< infoJuego.cantEnemigos(); i++) {
        spritesManager->renderizarEnemigo(i);
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
        spritesManager->renderizarProyectilEn(infoJuego.proyectiles[i].direccion, infoJuego.proyectiles[i].tipo, pos.x, pos.y);
        //spritesManager->updatePlayer(i, infoJuego.players[i].estado, posicion);
    }

    //HUD
    spritesManager->renderizarVidas(infoJuego.players[0].vida);
    spritesManager->renderizarMunicionArma(infoJuego.players[0].arma, infoJuego.players[0].municion);

    SDL_RenderPresent(renderer); // dibuja todo
}

void InterfazGrafica::nextEstado() {
    switch (estado)
    {
    case Menu:
        musicPlayer.play_music(SELECTION_MUSIC_PATH);
        estado = SeleccionPartida;
        renderizarPantalla = &InterfazGrafica::renderizarSeleccionPartida;
        break;
    case SeleccionPartida:
        estado = SeleccionPlayer;
        renderizarPantalla = &InterfazGrafica::renderizarSeleccionPlayer;
        break;
    case SeleccionPlayer:
        musicPlayer.play_music(MEDIVO_MUSIC_PATH); // TODO: modificar por música del mapa particular
        estado = Juego;
        renderizarPantalla = &InterfazGrafica::renderizarJuego;
        break;
    case Juego:
        musicPlayer.stop();
        estado = ResultadosFinales; //no implementado
        //renderizarPantalla = &InterfazGrafica::renderizarTablaResultados;
        break;
    case ResultadosFinales:
        musicPlayer.stop();
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
