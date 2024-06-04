#include "interfaz_grafica.h"
#include "client_protocol.h"
#include "client_receiver.h"
#include "client_sender.h"
#include "client_renderer.h"
#include "event_handler.h"
#include "client_player.h"

#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/constantes.h"
#include "../common_src/info_juego.h"

#define ACTION_WALK 0x12

#define MOV_IZQ "IZQ"
#define MOV_DER "DER"
#define EXIT "q"

#define ID_MSG_SIZE 1

#define EXIT_BYTE 0xFF

#define SUCCESS 0
#define ERROR 1


const int FPS = 15;
const int frame_delay = 1000/FPS;

int tiempo_transcurrido;

#define HOSTNAME argv[1]
#define SERVICENAME argv[2]


int main(int argc, char* argv[]) {
    std::string input;
    bool was_closed = false;
    
    ClientPlayer cliente = ClientPlayer(HOSTNAME, SERVICENAME);
    InterfazGrafica interfaz(cliente.queueReceptora);

    /*while(interfaz.estaAbierta() && interfaz.menuAbierto()) //Renderiza las diferentes pantallas
    {
        interfaz.renderizarActual();
        interfaz.manejarEventosActual();
    }
    */
    //ClientRenderer* renderer = new ClientRenderer(interfaz);
    //renderer->start();
    EventHandler eventHandler(interfaz, cliente);
    eventHandler.start();
    
    while (interfaz.estaAbierta())
    {
        int frameStart = SDL_GetTicks(); //obtengo el tiempo que paso desde que se inicializo SDL
        
        interfaz.recibirInformacion();
        interfaz.update(1);
        interfaz.renderizar();
        
        tiempo_transcurrido = SDL_GetTicks() - frameStart;
        if (frame_delay > tiempo_transcurrido) {
            SDL_Delay(frame_delay - tiempo_transcurrido); // sleep
        }
    }
    eventHandler.join();
    
    //renderer->join();
    std::cout << "fin" << std::endl;
    
    //finalmente
    //mostrar tabla final y ganador.
    return 0;
}