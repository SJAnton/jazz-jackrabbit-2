#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "../common_src/socket.h"
#include "../common_src/constantes_protocolo.h"
#include "../common_src/info_juego.h"
#include "../common_src/protocol.h"

#include <string>
#include <vector>
#include <arpa/inet.h>

class ClientProtocol : public Protocol {
	private:
		Socket socket;
		bool was_closed;
		uint8_t id;

	private:
		//obtiene el valor decimal contenido entre ambos bytes
		int decodeInt(uint8_t byte1, uint8_t byte2);
		//obtiene el valor decimal contenido en 1 byte
		int decodeInt(uint8_t byte);

		InfoPlayer decodePlayer(const std::vector<uint8_t> &bytes);
		InfoEnemigo decodeEnemy(const std::vector<uint8_t> &bytes);
		InfoRecolectable decodeRecolectable(const std::vector<uint8_t> &bytes);
		InfoProyectil decodeProyetil(const std::vector<uint8_t> &bytes);

		InfoJuego decodificarMensajeDelServer(const std::vector<uint8_t> &bytes);

	public:
		ClientProtocol(const std::string& hostname, const std::string& servname);

		// envia 2 bytes:
		// id partida (0 si es para crear una partida) y tipo de player
		void enviarMensajeInicial(int id_partida, TipoPlayer tipoPlayer, bool *was_closed);
		
		void enviarComando(ComandoCliente comando, bool*was_closed);

		InfoJuego recibirInformacion(bool *was_closed);
		std::vector<int> recibirIdsPartidas(bool *was_closed);
		void recibirIDCliente();
		//Terreno recibirTerreno(bool *was_closed);

		void close();
};

#endif
