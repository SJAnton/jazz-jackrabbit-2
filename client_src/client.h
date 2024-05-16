#ifndef CLIENT_H
#define CLIENT_H

#include "queue.h"

class Client{
	private:
		Queue<uint8_t>& queueReceptora; 
    	Queue<uint8_t>& queueEnviadora;

	public:
		Client(Queue<uint8_t>&, Queue<uint8_t>&);
		void moverIzquierda();
		void moverDerecha();
		void saltar();
		void correr();
		void disparar();
		void ataque_especial();
		void recibirInformacion();
};

#endif