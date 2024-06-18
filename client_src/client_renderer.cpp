#include "client_renderer.h"

ClientRenderer::ClientRenderer(InterfazGrafica* interfaz) : interfaz(interfaz){}

void ClientRenderer::run(){

	const int FPS = 50;
	const int frame_delay = 1000/FPS;

	int tiempo_transcurrido;

	while(interfaz->estaAbierta()){
		int frameStart = SDL_GetTicks();

		//interfaz->recibirInformacion();
        interfaz->update(1);
        interfaz->renderizarActual();

        tiempo_transcurrido = SDL_GetTicks() - frameStart;
        if (frame_delay > tiempo_transcurrido) {
            SDL_Delay(frame_delay - tiempo_transcurrido); // sleep
        }
	}
	interfaz->cerrarInterfaz(); 
}