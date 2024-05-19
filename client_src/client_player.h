#ifndef CLIENT_H
#define CLIENT_H

#include "../common_src/queue.h"
#include "../common_src/constantes.h"
class ClientPlayer{
	private:
		Queue<EstadosPlayer>& queueReceptora; 
    	Queue<AccionesPlayer>& queueEnviadora;

	public:
		ClientPlayer();
		ClientPlayer(Queue<EstadosPlayer>&, Queue<AccionesPlayer>&);
		void moverIzquierda();
		void moverDerecha();
		void saltar();
		void correr();
		void disparar();
		void ataque_especial();
		void recibirInformacion();
};

#endif