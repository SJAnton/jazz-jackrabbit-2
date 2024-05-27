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
}

bool InterfazGrafica::estaAbierta() {
    return is_running;
}

bool InterfazGrafica::menuAbierto(){
    return menu_abierto;
}


bool pointInsideRect(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}

void InterfazGrafica::manejarEventosMenu(){
    SDL_Event e;
    SDL_PollEvent(&e);

    if (e.type == SDL_QUIT) {
        is_running = false;
        return;
    } else if (e.type == SDL_KEYDOWN) {
        if(e.key.keysym.sym == SDLK_ESCAPE){
            is_running = false;
            return;
        }
    }else if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (pointInsideRect(mouseX, mouseY, {234, 258, 282, 84})) { //Chequea si se clickeo en la zona del boton
            std::cout << "Comienza el juego!" << std::endl;
            menu_abierto = false;
        }
    }
}

void InterfazGrafica::recibirInformacion(){
    //cliente.recibirInformacion();
    //Proceso la informacion para actualizar la interfaz
}
 

void InterfazGrafica::update(int it) {
    InfoJuego infoJuego;
    if (queueReceptora.try_pop(infoJuego)) {
        //std::cout << infoJuego.player1.pos.x << std::endl;
        //spritesManager->updatePlayer()
        spritesManager->updatePlayer(0,infoJuego.player1.estado, infoJuego.player1.pos);
        //spritesManager->setEstadoPlayer(0, infoJuego.player1.estado);
    }
    //recibirinformacion()
    //copiar toda la informacion seteandola en el spritemanager.
    //Por ej.:
    //spritesManager->setPositionPlayer(0, estadoJuego.getPlayer(0).position)
    //spritesManager->setEstadoPlayer(0, estadoJuego.getPlayer(0).estado)

    iteracion += it;
    /*if (iteracion % 3 == 0) {
        spritesManager->nextFramePlayer(0);
    }
    if (iteracion % 4 == 0) {
        spritesManager->nextFramePlayer(1);
    }
    if (iteracion % 4 == 0) {
        spritesManager->nextFramePlayer(2);
    }*/

    
} 

void InterfazGrafica::renderizar() 
{
    SDL_RenderClear(renderer);//borra todo

    //cargar todos los pixeles (fondo, terreno, objetos, players, etc)
    //(ejemplo)
    spritesManager->renderizarFondo();
    spritesManager->renderizarPlayerEn(0, 244, 256);

    SDL_RenderPresent(renderer); // dibuja todo
}
void InterfazGrafica::stop(){
    is_running = false;
} 


void InterfazGrafica::renderizarMenu(){
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 1);
    SDL_RenderClear(renderer);

    SDL_Surface* surface_button = IMG_Load("../sprites/boton_play.png");
    SDL_Texture* texture_button = SDL_CreateTextureFromSurface(renderer, surface_button);
    SDL_FreeSurface(surface_button);
    SDL_Rect buttonRect = {234, 258, 282, 84};

    SDL_RenderCopy(renderer, texture_button, nullptr, &buttonRect);
    SDL_DestroyTexture(texture_button);

    SDL_Surface* surface = IMG_Load("../sprites/titulo.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect imageRect = {95, 28, 560, 224};

    SDL_RenderCopy(renderer, texture, nullptr, &imageRect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
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
