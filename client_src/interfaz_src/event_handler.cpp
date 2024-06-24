#include "event_handler.h"
#include "interfaz_grafica.h"
#include <iostream>
#include "../../common_src/constantes.h"

EventHandler::EventHandler(InterfazGrafica &interfaz, ClientPlayer &clientPlayer, 
                           const std::list<ButtonPartida> &partidas,
                           const std::list<ButtonCharacter> &personajes) : 
        interfaz(interfaz),
        cliente(clientPlayer),
        partidas(partidas),
        personajes(personajes)
{
}

void EventHandler::run()
{
    SDL_Event e;
    int frameStart;
    Direcciones dir = Direcciones::Right;
    while (_keep_running) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                interfaz.stop();
                stop();
                return;
            } 
            switch (interfaz.getEstado())
            {
            case Menu:
                manejarEventosMenu(e);
                break;
            case SeleccionPartida:
                manejarSeleccionPartida(e);
                break;
            case SeleccionPlayer: 
                manejarSeleccionPlayer(e);
                break;;
            case Juego:
                manejarComandosJuego(e, dir);
                break;
            case ResultadosFinales: //IMPLEMENTAR
                break;
            default:
                break;
            }
        }
        procesarEstadoTeclas(dir);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (1000 / 15 > frameTime) {
            SDL_Delay(1000 / 15 - frameTime); // sleep 
        }
    }
}
bool pointInsideRect(int x, int y, SDL_Rect rect) { //.
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}

void EventHandler::manejarEventosMenu(SDL_Event &e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        int separacion = 100;
        int boton_width = 282, boton_height = 84;
        int boton_x = (ANCHO_WINDOW - boton_width) / 2;
        int boton_y = ((ALTO_WINDOW - boton_height) / 2) + separacion;

        if (pointInsideRect(mouseX, mouseY, {boton_x, boton_y, boton_width, boton_height})) { //Chequea si se clickeo en la zona del boton
            std::cout << "Seleccione una partida" << std::endl;
            interfaz.nextEstado();
        }
    }
}

void EventHandler::manejarSeleccionPartida(SDL_Event &e){
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        for (auto partida : partidas) { //Recorro las partidas
            if (partida.clicked(mouseX, mouseY)) { //Chequea si se clickeo en la zona del boton
                std::cout << "Seleccione un personaje" << std::endl;
                partidaSeleccionada = partida.getIdPartida();
                interfaz.nextEstado();
                //cliente.entrarPartida(partidaSeleccionada, TipoPlayer::Spaz);//hardcodeado
                //cliente.recibirInformacion();
                //interfaz.nextEstado();
                return;
            }
        }

        int cant_letras_texto = 13, size_letras = 32;
        int texto_width = (size_letras * cant_letras_texto);
        int x = (ANCHO_WINDOW - texto_width) / 2;
        int y = ALTO_WINDOW - 100;

        if (pointInsideRect(mouseX, mouseY, {x, y, texto_width, size_letras})) { //Chequea si se clickeo en la zona del boton
            std::cout << "Creando partida nueva" << std::endl;
            partidaSeleccionada = 0;
            interfaz.nextEstado();
            //cliente.entrarPartida(partidaSeleccionada, TipoPlayer::Spaz);//hardcodeado
            //interfaz.nextEstado();
        }

    }
}

void EventHandler::manejarSeleccionPlayer(SDL_Event &e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        for (auto personaje : personajes) { //Recorro los personajes
            if (personaje.clicked(mouseX, mouseY)) { //Chequea si se clickeo en la zona del boton
                std::cout << "Comienza el juego!" << std::endl;
                TipoPlayer personajeSeleccionado = personaje.getTipoPlayer();
                interfaz.addPlayer(personajeSeleccionado);
                cliente.entrarPartida(partidaSeleccionada, personajeSeleccionado);
                cliente.recibirInformacion();
                //TileMap mapa = cliente.recibirMapa();
                interfaz.setMapa(cliente.recibirMapa());
                interfaz.nextEstado();

                return;
            }
        }
    }
}

void EventHandler::manejarComandosJuego(SDL_Event &e, Direcciones &dir) {
    if (e.type == SDL_KEYDOWN) {
        key_state[e.key.keysym.sym] = true;
    } else if (e.type == SDL_KEYUP) {
        key_state[e.key.keysym.sym] = false;
    }
}

void EventHandler::procesarEstadoTeclas(Direcciones &dir) {
    if (key_state[SDLK_SPACE]) {
        cliente.saltar(dir);
    }
    if (key_state[SDLK_LEFT]) {
        dir = Direcciones::Left;
        //interfaz.flipPlayer(true);
        if (SDL_GetModState() & KMOD_LCTRL) // Se presionó Ctrl + Izquierda
            cliente.correr(dir);
        else
            cliente.caminar(dir);
    }
    if (key_state[SDLK_RIGHT]) {
        dir = Direcciones::Right;
        if (SDL_GetModState() & KMOD_LCTRL) // Se presionó Ctrl + Derecha
            cliente.correr(dir);
        else
            cliente.caminar(dir);
    }
    if (key_state[SDLK_d]) {
        cliente.disparar(dir);
    }
    if (key_state[SDLK_c]) {
        cliente.cambiar_arma(dir);
    }
    if (key_state[SDLK_a]) {
        cliente.ataque_especial(dir);
    }
}
