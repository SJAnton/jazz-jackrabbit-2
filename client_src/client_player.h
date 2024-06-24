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
		std::vector<int> ids_partidas;
		std::vector<std::string> nombres_niveles;
	public:
		static Queue<ComandoCliente> queueEnviadora;
		static Queue<InfoJuego> queueReceptora;

	public:
		ClientPlayer(const std::string& hostname, const std::string& servname);

		void caminar(Direcciones direccion);
		void saltar(Direcciones direccion);
		void correr(Direcciones direccion);
		void disparar(Direcciones direccion);
		void ataque_especial(Direcciones direccion);
		void cambiar_arma(Direcciones direccion);
		
		void recibirInformacion();
		TileMap recibirMapa();

		void crearPartida(const TipoPlayer &TipoPlayer);
		void entrarPartida(int idPartida, const TipoPlayer &TipoPlayer);

		std::vector<int> getIdPartidas();
		std::vector<std::string> getNombresNiveles();
		~ClientPlayer();
};

#endif