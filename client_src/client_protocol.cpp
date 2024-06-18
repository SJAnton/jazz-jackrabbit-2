#include "client_protocol.h"

#include <vector>
#include <exception>
#include <iostream>
#include <iomanip>

#define MULTIPLICADOR_POSICION 4


ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname) :
	socket(hostname.c_str(), servname.c_str()),
	was_closed(false)
{
}

int ClientProtocol::decodeInt(uint8_t byte) {
    return static_cast<int>(byte);
}
int ClientProtocol::decodeInt(uint8_t byte1, uint8_t byte2) {
    uint16_t network_value = (static_cast<uint16_t>(byte1) << 8) | byte2;
    int host_value = ntohs(network_value);
    
	return host_value;
}

InfoPlayer ClientProtocol::decodePlayer(const std::vector<uint8_t> &bytes) {
	int id = decodeInt(bytes[0]);
	int pos_x = decodeInt(bytes[1], bytes[2]);// * MULTIPLICADOR_POSICION;
	int pos_y = decodeInt(bytes[3], bytes[4]);// * MULTIPLICADOR_POSICION;
	Direcciones dir = decodeDireccion(bytes[5]);
	TipoPlayer tipo = decodeTipoPlayer(bytes[6]);
	EstadosPlayer estado = decodeEstadoPlayer(bytes[7]);
	int vida = decodeInt(bytes[8]);
	int pts = decodeInt(bytes[9]);
	TipoArma arma =  decodeTipoArma(bytes[10]);
	int municion = decodeInt(bytes[11]);
	return InfoPlayer(id, pos_x, pos_y, dir, tipo, estado, vida, pts, arma, municion);
}


InfoEnemigo ClientProtocol::decodeEnemy(const std::vector<uint8_t> &bytes) {
	TipoEnemy tipo = decodeTipoEnemy(bytes[0]);
	int pos_x = decodeInt(bytes[1], bytes[2]);// * MULTIPLICADOR_POSICION;
	int pos_y = decodeInt(bytes[3], bytes[4]);// * MULTIPLICADOR_POSICION;
	Direcciones dir = decodeDireccion(bytes[5]);
	EstadosEnemy estado = decodeEstadoEnemy(bytes[6]);

	return InfoEnemigo(tipo, pos_x, pos_y, dir, estado);
}

// modularizarlo despues
// nota. EL PLAYER 0 DEBE SER EL QUE COINCIDA CON EL ID DEL CLIENTE (FUNDAMENTAL)
InfoJuego ClientProtocol::decodificarMensajeDelServer(const std::vector<uint8_t> &bytes) {
	int cantPlayers = decodeInt(bytes[0]);
	if (cantPlayers* LENGTH_PLAYER_INFO > bytes.size()){
		std::runtime_error("Error en el mensaje recibido. En ClientProtocol::decodificarMensajeDelServer()");
	}
	int contador = 1;
	
	std::vector<InfoPlayer> infoPlayers;
	std::vector<InfoEnemigo> infoEnemies;
	std::vector<InfoRecolectable> infoItems;
	std::vector<InfoProyectil> infoProyectiles;

	//Decode info Players
	for (int i = 0; i < cantPlayers; i++) { 
		if (contador + LENGTH_PLAYER_INFO > bytes.size()) {
			std::runtime_error("Error. Faltaron datos de un player. En ClientProtocol::decodificarMensajeDelServer()");
		}
		std::vector<uint8_t> playerBytes(bytes.begin() + contador, bytes.begin() + contador + LENGTH_PLAYER_INFO);
        InfoPlayer player = decodePlayer(playerBytes);
        infoPlayers.push_back(player);

	    contador += LENGTH_PLAYER_INFO;
	}
	
	int cantEnemigos = decodeInt(bytes[contador]);
	contador++;
	//Decode info Enemigos
	for (int i = 0; i < cantEnemigos; i++) { 
		if (contador + LENGTH_ENEMY_INFO > bytes.size()) {
			std::runtime_error("Error. Faltaron datos de un enemigo. En ClientProtocol::decodificarMensajeDelServer()");
		}
		std::vector<uint8_t> enemyBytes(bytes.begin() + contador, bytes.begin() + contador + LENGTH_ENEMY_INFO);
		infoEnemies.push_back(decodeEnemy(enemyBytes));
		
		contador += LENGTH_ENEMY_INFO;
	}
	
	int cantItems = decodeInt(bytes[contador]);
	contador++;

	//Decode info Recolectables
	for (int i = 0; i < cantItems; i++) { 
		if (contador + LENGTH_ITEMS_INFO > bytes.size())
			std::runtime_error("Error. Faltaron datos de un item recolectable. En ClientProtocol::decodificarMensajeDelServer()");
		
		TipoRecolectable tipo = decodeTipoRecolectable(bytes[contador]); 
		int pos_x = decodeInt(bytes[contador+1], bytes[contador+2]);// * MULTIPLICADOR_POSICION;
		int pos_y = decodeInt(bytes[contador+3], bytes[contador+4]);// * MULTIPLICADOR_POSICION;

		infoItems.emplace_back(tipo, pos_x, pos_y);
		contador += LENGTH_ITEMS_INFO;
	}
	int cantProyectiles = decodeInt(bytes[contador]);
	contador++;

	//Decode info proyectiles
	for (int i = 0; i < cantProyectiles; i++) { 
		if (contador + LENGTH_PROYECTIL_INFO > bytes.size())
			std::runtime_error("Error. Faltó info de un proyectil. En ClientProtocol::decodificarMensajeDelServer()");
		TipoArma tipo = decodeTipoArma(bytes[contador]);
		int pos_x = decodeInt(bytes[contador+1], bytes[contador+2]);// * MULTIPLICADOR_POSICION;
		int pos_y = decodeInt(bytes[contador+3], bytes[contador+4]);// * MULTIPLICADOR_POSICION;
		Direcciones dir = decodeDireccion(bytes[contador+5]);

		infoProyectiles.emplace_back(tipo, pos_x, pos_y, dir);
		contador += LENGTH_PROYECTIL_INFO;
	}
//	std::cout << "Recibi proyectiles" << cantProyectiles<< std::endl;

	return InfoJuego(infoPlayers, infoEnemies, infoItems, infoProyectiles);
}


//metodos publicos

void ClientProtocol::enviarComando(ComandoCliente comando, bool*was_closed_) {
	std::vector<uint8_t> mensaje;
	if (comando.getTipoComando() == MensajeInicial) {
		std::cout << "me uno a la partida" << std::endl;
		mensaje.push_back((uint8_t)comando.getIdPartida());
		mensaje.push_back(encodeTipoPlayer(comando.getTipoPlayer()));
	}
	else { //Accion de un player
		mensaje.push_back(id); // necesito saber mi ID de cliente
		mensaje.push_back(encodeAccion(comando.getAccion()));
		mensaje.push_back(encodeDireccion(comando.getDireccion()));
	}
	socket.sendall(mensaje.data(), mensaje.size(), &was_closed);	
	*was_closed_= was_closed;
	//std::cout << "se enviaron " << enviados << " bytes." << std::endl;
}

InfoJuego ClientProtocol::recibirInformacion(bool *was_closed_) {
	uint8_t aux[2];
	int r = socket.recvall(&aux, sizeof(aux), &was_closed);	//recibo los primeros 2 bytes que indican el size del mensaje
	if (was_closed) {
		*was_closed_ = was_closed;
		std::cout << "wasclosed " << std::endl;//no se está activando esto
		return InfoJuego();
	}

	int size = decodeInt(aux[0], aux[1]);
	//std::cout << "size " << size<< std::endl;//no se está activando esto
	
    std::vector<uint8_t> bytes(size);
	r = socket.recvall(bytes.data(), size, &was_closed);
	if (was_closed) {
		*was_closed_ = true;
		std::cout << "wasclosed " << std::endl;//no se está activando esto
		return InfoJuego();

	}
	/*std::cout << "Mensaje recibido: ";
		for (uint8_t byte : bytes) {
			std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
		}
		std::cout << std::endl;
	*/
	InfoJuego infoJuego = decodificarMensajeDelServer(bytes);
	return infoJuego;
}

std::vector<int> ClientProtocol::recibirIdsPartidas(bool *was_closed_)
 {
	uint8_t size;
    socket.recvall(&size, sizeof(size), &was_closed); // recibo 1 byte con el size

	std::vector<uint8_t> bytes(size);
	socket.recvall(bytes.data(), size, &was_closed); // recibo los id de las partidas
	*was_closed_ = was_closed;
	// Convertimos los bytes recibidos a un vector de enteros
    std::vector<int> idsPartidas(size);
    for (size_t i = 0; i < size; ++i) {
        idsPartidas[i] = static_cast<int>(bytes[i]);
    }
    return idsPartidas;
}

void ClientProtocol::recibirIDCliente() {
	uint8_t byte;
	int r = socket.recvall(&byte, sizeof(byte), &was_closed);	
	this->id = byte;
}


void ClientProtocol::close() {
	socket.shutdown(2);
	socket.close();
}

