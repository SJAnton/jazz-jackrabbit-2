#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "../common_src/socket.h"
#include "../common_src/constantes_protocolo.h"
#include "../common_src/info_juego.h"

#include <string>
#include <arpa/inet.h>

class ClientProtocol{
	private:
		Socket socket;

	private:
		uint8_t codeAccion(AccionesPlayer accion);
		uint8_t codeDireccion(Direcciones direccion);

		//obtiene el valor decimal contenido entre ambos bytes
		int decodeInt(uint8_t byte1, uint8_t byte2);
		//obtiene el valor decimal contenido en 1 byte
		int decodeInt(uint8_t byte);
		EstadosPlayer decodeEstadoPlayer(uint8_t byte);
		InfoJuego decodificarMensajeDelServer(const std::vector<uint8_t> &bytes);


	public:
		ClientProtocol(const std::string& hostname, const std::string& servname);
		//ClientProtocol(Socket& socket);
		//uint8_t recv_action(bool&);
		InfoJuego recibirInformacionDelServer(bool *was_closed);
		void enviarComandoAlServer(ComandoCliente comando, bool*was_closed);
		//int send_action(uint8_t&, bool&);
};

#endif
