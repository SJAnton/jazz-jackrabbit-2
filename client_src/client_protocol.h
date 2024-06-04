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

	private:
		uint8_t codeAccion(AccionesPlayer accion);
		uint8_t codeDireccion(Direcciones direccion);

		//obtiene el valor decimal contenido entre ambos bytes
		int decodeInt(uint8_t byte1, uint8_t byte2);
		//obtiene el valor decimal contenido en 1 byte
		int decodeInt(uint8_t byte);
		EstadosPlayer decodeEstadoPlayer(uint8_t byte);
		TipoEnemy decodeTipoEnemy(uint8_t byte);
		EstadosEnemy decodeEstadoEnemy(uint8_t byte);
		Direcciones decodeDireccion(uint8_t dir);


		InfoJuego decodificarMensajeDelServer(const std::vector<uint8_t> &bytes);

	public:
		ClientProtocol(const std::string& hostname, const std::string& servname);

		void enviarMensajeInicialAlServer(bool*was_closed);
		
		void enviarComandoAlServer(ComandoCliente comando, bool*was_closed);
		
		InfoJuego recibirInformacionDelServer(bool *was_closed);
		
};

#endif
