#ifndef CLIENT_H
#define CLIENT_H

class ClientPlayer{
	private:

	public:
		ClientPlayer();
		void moverIzquierda();
		void moverDerecha();
		void saltar();
		void correr();
		void disparar();
		void ataque_especial();
		void recibirInformacion();
};

#endif