#ifndef CLIENT_H
#define CLIENT_H

#include "../common_src/queue.h"
#include "../common_src/constantes.h"
#include "client_protocol.h"
#include "client_sender.h"
#include "client_receiver.h"

class ClientPlayer{
	private:
		ClientProtocol protocolo;
		ClientReceiver receiver;
		ClientSender sender;
		static Queue<ComandoCliente> queueEnviadora;

	public:
		static Queue<InfoJuego> queueReceptora;

	public:
		ClientPlayer(const std::string& hostname, const std::string& servname);
		//ClientPlayer(Queue<InfoJuego>&, Queue<AccionesPlayer>&);
		void caminar(Direcciones direccion);
		void saltar(Direcciones direccion);
		void correr(Direcciones direccion);
		void disparar(Direcciones direccion);
		void ataque_especial(Direcciones direccion);
		
		void recibirInformacion();
		~ClientPlayer();
};

#endif