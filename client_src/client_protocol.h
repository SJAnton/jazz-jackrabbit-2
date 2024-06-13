#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "../common_src/socket.h"
#include "../common_src/constantes_protocolo.h"
#include "../common_src/info_juego.h"

#include <string>
#include <vector>
#include <arpa/inet.h>

class ClientProtocol{
	private:
		Socket socket;
		bool was_closed;
		uint8_t id;

	private:
		uint8_t codeAccion(AccionesPlayer accion);
		uint8_t codeDireccion(Direcciones direccion);
		uint8_t codeTipoPlayer(const TipoPlayer &tipo);
		
		//obtiene el valor decimal contenido entre ambos bytes
		int decodeInt(uint8_t byte1, uint8_t byte2);
		//obtiene el valor decimal contenido en 1 byte
		int decodeInt(uint8_t byte);
		EstadosPlayer decodeEstadoPlayer(uint8_t byte);
		TipoEnemy decodeTipoEnemy(uint8_t byte);
		EstadosEnemy decodeEstadoEnemy(uint8_t byte);
		TipoPlayer decodeTipoPlayer(uint8_t byte);
		Direcciones decodeDireccion(uint8_t dir);

		InfoPlayer decodePlayer(const std::vector<uint8_t> &bytes);
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

		//temporal
		uint8_t get_msg_size(bool &was_closed);
		int send_msg(std::vector<uint8_t> data, bool &was_closed);
		std::vector<uint8_t> recv_msg(int size, bool &was_closed);

};

#endif
