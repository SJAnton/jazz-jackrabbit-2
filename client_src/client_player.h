#ifndef CLIENT_H
#define CLIENT_H

<<<<<<< HEAD:client_src/client_player.h
class ClientPlayer{
=======
#include "queue.h"

class Client{
>>>>>>> 7f6ca1733e9999b5e6ec9bbea09ca6b6a6448e02:client_src/client.h
	private:
		Queue<uint8_t>& queueReceptora; 
    	Queue<uint8_t>& queueEnviadora;

	public:
<<<<<<< HEAD:client_src/client_player.h
		ClientPlayer();
=======
		Client(Queue<uint8_t>&, Queue<uint8_t>&);
>>>>>>> 7f6ca1733e9999b5e6ec9bbea09ca6b6a6448e02:client_src/client.h
		void moverIzquierda();
		void moverDerecha();
		void saltar();
		void correr();
		void disparar();
		void ataque_especial();
		void recibirInformacion();
};

#endif