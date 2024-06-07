#include "interfaz_grafica.h"

#include "sprite_object.h"
#include "spritesheet.h"
#include "spritesManager.h"
#include "characters.h"


SDL_Renderer* InterfazGrafica::renderer = nullptr;

//constructor
InterfazGrafica::InterfazGrafica(Queue<InfoJuego> &queueReceptora) : 
    queueReceptora(queueReceptora), renderizarPantalla(&InterfazGrafica::renderizarMenu), 
    manejarEventos(&InterfazGrafica::manejarEventosMenu)
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

    infoJuego.addPlayer();
    /*infoJuego.player1.estado = EstadosPlayer::Inactivo;
    infoJuego.player1.pos = Position(0, 256);
    infoJuego.player1.vida = 10;
    infoJuego.player1.puntos = 0 ;
    */
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
            std::cout << "Seleccione una partida" << std::endl;
            //menu_abierto = false;
            renderizarPantalla = &InterfazGrafica::renderizarSeleccionPartida;
            manejarEventos = &InterfazGrafica::manejarEventosSeleccionPartida;

        }
    }
}

void InterfazGrafica::manejarEventosSeleccionPartida(){
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

        for (auto partida : partidas) { //Recorro las partidas
            if (partida.clicked(mouseX, mouseY)) { //Chequea si se clickeo en la zona del boton
                std::cout << "Comienza el juego!" << std::endl;
                //Mandar mensaje al server con el ID de la partida
                menu_abierto = false;
                break;
            }
        }

        if (pointInsideRect(mouseX, mouseY, {416, 32, 167, 400})) { //Chequea si se clickeo en la zona del boton
            std::cout << "Creando partida nueva" << std::endl;
            menu_abierto = false;
        }

    }
}

void InterfazGrafica::recibirInformacion(){
    //cliente.recibirInformacion();
    //Proceso la informacion para actualizar la interfaz
}
 

void InterfazGrafica::update(int it) {
    iteracion += it;
    
    /*if (queueReceptora.try_pop(infoJuego)) {//Debe ser bloqueante?
        if (infoJuego.players[0].estado == EstadosPlayer::Jumping)
            std::cout << "dibujo saltar" << std::endl;
    }
    */
    infoJuego = queueReceptora.pop();
    Position pos(infoJuego.players[0].pos_x, infoJuego.players[0].pos_y);
    spritesManager->updatePlayer(0, infoJuego.players[0].estado, pos);

    
    
} 
void InterfazGrafica::flipPlayer(bool flip) {
    spritesManager->flipPlayer(0, flip);
}
void InterfazGrafica::renderizar() 
{
    SDL_RenderClear(renderer);//borra todo
    spritesManager->renderizarFondo();
    spritesManager->renderizarPlayer(0);

    SDL_RenderPresent(renderer); // dibuja todo
}
void InterfazGrafica::stop(){
    is_running = false;
} 

void InterfazGrafica::renderizarActual(){
    (this->*renderizarPantalla)();
}

void InterfazGrafica::manejarEventosActual(){
    (this->*manejarEventos)();
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

void renderText(SDL_Renderer* renderer, SDL_Texture* texture, const std::unordered_map<char,
                SDL_Rect>& charMap, const std::string& text, int x, int y, float scale) {
    for (char c : text) {
        auto it = charMap.find(c);
        if (it != charMap.end()) { // Si se encuentra el carácter en el mapa
            SDL_Rect srcRect = it->second;
            SDL_Rect dstRect = { x, y, static_cast<int>(srcRect.w * scale), 
                                static_cast<int>(srcRect.h * scale) };
            SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
            x += dstRect.w;
        } else if (c == ' ') { // Si el carácter es un espacio
            x += static_cast<int>(64 * scale); // Avanza el ancho de un espacio
        }
    }
}

void InterfazGrafica::renderizarSeleccionPartida(){
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 1);
    SDL_RenderClear(renderer);

    Characters fontMap = Characters();

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

    renderText(renderer, fontTexture, fontMap.charMap, "CREAR PARTIDA", 167, 400, 0.5f);  

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
