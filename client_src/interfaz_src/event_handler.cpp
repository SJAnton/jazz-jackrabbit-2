#include "event_handler.h"
#include "interfaz_grafica.h"
#include <iostream>
#include "../../common_src/constantes.h"

EventHandler::EventHandler(InterfazGrafica &interfaz, ClientPlayer &clientPlayer, 
                           const std::list<ButtonPartida> &partidas,
                           const std::list<ButtonCharacter> &personajes) : 
        interfaz(interfaz),
        cliente(clientPlayer),
        partidas(partidas)
{
}

void EventHandler::run()
{
    SDL_Event e;
    int frameStart;
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
                break;;
            case Juego: 
                manejarComandosJuego(e);
                break;
            case ResultadosFinales:
                break;
            default:
                break;
            }
        }

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
        if (pointInsideRect(mouseX, mouseY, {234, 258, 282, 84})) { //Chequea si se clickeo en la zona del boton
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
                std::cout << "Comienza el juego!" << std::endl;
                partidaSeleccionada = partida.getIdPartida();
                interfaz.nextEstado();
                //cliente.entrarPartida(partidaSeleccionada, TipoPlayer::Spaz);//hardcodeado
                //cliente.recibirInformacion();
                //interfaz.nextEstado();
                return;
            }
        }

        //ARREGLAR ESTO PARA QUE NO ESTE HARDCODEADO
        if (pointInsideRect(mouseX, mouseY, {416, 32, 167, 400})) { //Chequea si se clickeo en la zona del boton
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
                cliente.entrarPartida(partidaSeleccionada, personajeSeleccionado);
                cliente.recibirInformacion();
                interfaz.nextEstado();

                return;
            }
        }
    }
}

void EventHandler::manejarComandosJuego(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        Direcciones dir = Direcciones::Right;
        switch (e.key.keysym.sym) { // Obtengo el código de la tecla presionada
        case SDLK_SPACE: 
            cliente.saltar(dir);
            break;
        case SDLK_LEFT:
            dir = Direcciones::Left;
            interfaz.flipPlayer(true);
            if (SDL_GetModState() & KMOD_LCTRL) // Se presionó Ctrl + Izquierda
                cliente.correr(dir);
            else
                cliente.caminar(dir);
            break;
        case SDLK_RIGHT:
            dir = Direcciones::Right;
            interfaz.flipPlayer(false);
            if (SDL_GetModState() & KMOD_LCTRL) // Se presionó Ctrl + Derecha
                cliente.correr(dir);
            else
                cliente.caminar(dir);
            break;
        case SDLK_d:
            cliente.disparar(dir);
            break;
        case SDLK_a: 
            cliente.ataque_especial(dir);
            break;
        default:
            break;
        }
    }
}
