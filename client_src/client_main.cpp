
#include "interfaz_grafica.h"
#include "../common_src/socket.h"
#include "client_player.h"

const int FPS = 50;
const int frame_delay = 1000/FPS;

int tiempo_transcurrido;

#define HOSTNAME argv[1]
#define SERVICENAME argv[2]


int main(int argc, char* argv[]) {

    //Socket skt(HOSTNAME, SERVICENAME);
    ClientPlayer cliente = ClientPlayer();

    InterfazGrafica interfaz(cliente);
    while (interfaz.estaAbierta())
    {
        int frameStart = SDL_GetTicks(); //obtengo el tiempo que paso desde que se inicializo SDL

        interfaz.manejarEventos();
        interfaz.recibirInformacion();
        interfaz.update(1);
        interfaz.renderizar();

        tiempo_transcurrido = SDL_GetTicks() - frameStart;
        if (frame_delay > tiempo_transcurrido) {
            SDL_Delay(frame_delay - tiempo_transcurrido); // sleep
        }
    }
    interfaz.cerrarInterfaz(); 
    std::cout << "fin" << std::endl;

    //conectarse al server
    //inicializar cliente
    //esperar confirmacion para iniciar (esperar a que se conecten los n clientes).


    //inicializar interfaz grafica

    //inicia bucle (hasta que el contador llegue a 0)
        //leer de entrada estandar (qué teclas se presionan)
        //recibir informacion de los estados y posiciones de todos los elementos
        //actualizar estados y posiciones de todas las imagenes. (si no recibio nada, mantienen los que tenian)
        //si mantuvieron el estado, avanzar al siguiente frame de cada animacion (segun corresponda)
        //pintar

        //hacer un sleep de ? milisegundos
        //contador--

    //finalmente
    //mostrar tabla final y ganador.
    return 0;
}