#include "interfaz_src/interfaz_grafica.h"
#include "client_protocol.h"
#include "client_receiver.h"
#include "client_sender.h"
#include "client_player.h"

#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/constantes.h"
#include "../common_src/info_juego.h"


const int FPS = 15;
const int frame_delay = 1000/FPS;

int tiempo_transcurrido;

#define HOSTNAME argv[1]
#define SERVICENAME argv[2]


int main(int argc, char* argv[]) {
    std::string input;
    bool was_closed = false;
    
    ClientPlayer cliente = ClientPlayer(HOSTNAME, SERVICENAME);
    InterfazGrafica interfaz(cliente.queueReceptora, cliente);
    
    while (interfaz.estaAbierta()) // hacer a la interfaz un thread y hacer interfaz.start(). No hace falta un hilo renderer
    {

        int frameStart = SDL_GetTicks(); //obtengo el tiempo que paso desde que se inicializo SDL
        
        //interfaz.recibirInformacion();
        interfaz.update(1);
        interfaz.renderizarActual();
        
        tiempo_transcurrido = SDL_GetTicks() - frameStart;
        if (frame_delay > tiempo_transcurrido) {
            SDL_Delay(frame_delay - tiempo_transcurrido); // sleep
        }
        
        
    }    

    std::cout << "fin" << std::endl;
    
    return 0;
}