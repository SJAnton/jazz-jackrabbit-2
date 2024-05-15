#include "interfaz_grafica.h"

#include "sprite_object.h"
#include "spritesheet.h"
#include "client.h"

//GameObject *player1;
SpriteSheet *player1;
int x_player = 0;
//constructor
InterfazGrafica::InterfazGrafica(Client& cliente) : cliente(cliente)
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
    player1 = new SpriteSheet(renderer, "../../sprites/Players/Spazz/Idle (56x56)x06.png", 56, 56, 6);
    //cliente = Client();
}

bool InterfazGrafica::estaAbierta() {
    return is_running;
}


//creo el rectangulo con el tamaño recibido, para una textura
SDL_Rect InterfazGrafica::crearRect(int height, int width, int x, int y) {
    SDL_Rect rect_destino;
    rect_destino.w = width;
    rect_destino.h = height;
    rect_destino.x = x;
    rect_destino.y = y;
    return rect_destino;
}

void InterfazGrafica::manejarEventos()
{
    SDL_Event e;
    SDL_PollEvent(&e);

    if (e.type == SDL_QUIT) {
        is_running = false;
        return;

    } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) { //Obtengo el codigo de cada tecla
            case SDLK_SPACE:
                cliente.saltar();
                break;
            case SDLK_LEFT:
                cliente.moverIzquierda();
                break;
            case SDLK_RIGHT:
                cliente.moverDerecha();
                break;
            case SDLK_a:
                cliente.disparar();
                break;
            case SDLK_d:
                cliente.ataque_especial();
                break;
            //case correr a definir
            case SDLK_ESCAPE:
                is_running = false;
                break;

            default:
                break;
        }
    }
}

void InterfazGrafica::recibirInformacion(){
    cliente.recibirInformacion();
    //Proceso la informacion para actualizar la interfaz
}
 

void InterfazGrafica::update(int it) {
    iteracion += it;
    if (iteracion % 5 == 0)
        player1->nextFrame();
} 

void InterfazGrafica::renderizar() 
{
    SDL_RenderClear(renderer);//borra todo

    //cargar todos los pixeles (fondo, terreno, objetos, players, etc)
    //(ejemplo)
    player1->renderizar();
    
    //SDL_RenderCopy(renderer, texture, &rect, &rectPos);


    SDL_RenderPresent(renderer); // dibuja todo
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
