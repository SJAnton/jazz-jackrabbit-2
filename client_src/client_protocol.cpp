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
//metodos privados
uint8_t ClientProtocol::codeAccion(AccionesPlayer accion) {
	switch (accion) {
		case AccionesPlayer::Idle: return ACTION_IDLE;
		case AccionesPlayer::Walk: return ACTION_WALK;
		case AccionesPlayer::Run: return ACTION_RUN;
		case AccionesPlayer::Jump: return ACTION_JUMP;
		case AccionesPlayer::Shoot: return ACTION_SHOOT;
		case AccionesPlayer::SpecialAttack: return ACTION_SPECIAL_ATTACK;
		default: 
		throw std::runtime_error("ERROR. Accion invalida");
		return ACTION_IDLE;
	}
}
uint8_t ClientProtocol::codeDireccion(Direcciones direccion) {
	switch (direccion) {
		case Left: return LEFT;
		case Right: return RIGHT;
		default: 
		throw std::runtime_error("ERROR. Direccion invalida");
		return RIGHT;
	}
}
uint8_t ClientProtocol::codeTipoPlayer(const TipoPlayer &tipo) {
	switch (tipo) {
		case Jazz: return PLAYER_TYPE_JAZZ;
		case Lori: return PLAYER_TYPE_LORI;
		case Spaz: return PLAYER_TYPE_SPAZ;
		default: 
			throw std::runtime_error("ERROR. Tipo PLayer invalido");
			return PLAYER_TYPE_JAZZ;
	}
}
Direcciones ClientProtocol::decodeDireccion(uint8_t dir) {
	switch (dir) {
		case LEFT: return Left;
		case RIGHT: return Right;
		default: 
		throw std::runtime_error("ERROR. Direccion invalida. ClientProtocol::decodeDireccion()");
		return Right;
	}
}

EstadosPlayer ClientProtocol::decodeEstadoPlayer(uint8_t byte) {
    switch (byte) {
        case STATE_IDLE: return EstadosPlayer::Inactive;
        case STATE_WALK: return EstadosPlayer::Walking;
        case STATE_RUN: return EstadosPlayer::Running;
        case STATE_JUMP: return EstadosPlayer::Jumping;
        case STATE_FALL: return EstadosPlayer::Falling;
        case STATE_SHOOT: return EstadosPlayer::Shooting;
        case STATE_SPECIAL_ATTACK: return EstadosPlayer::SpecialAttack;
        case STATE_INTOXICATED_IDLE: return EstadosPlayer::IntoxicatedIdle;
		case STATE_INTOXICATED_WALK: return EstadosPlayer::IntoxicatedWalk;
        case STATE_DAMAGED: return EstadosPlayer::Damaged;
        case STATE_DYING: return EstadosPlayer::Dying;
        case STATE_DEAD: return EstadosPlayer::Dead;
        case STATE_REVIVE: return EstadosPlayer::Reviving;
        default: 
		throw std::runtime_error("ERROR. EstadoPlayer invalido. Probablemente estas pasando un byte que corresponde a otra cosa");
		return EstadosPlayer::Inactive;
    }
}
TipoEnemy ClientProtocol::decodeTipoEnemy(uint8_t byte) {
	switch (byte)
	{
	case ENEMY_RAT : return Rat;
	case ENEMY_BAT : return Bat;
	case ENEMY_LIZARD : return Lizard;	
	default:
		std::runtime_error("enemigo no existe. Probablemente se recibio un byte que corresponde a ora cosa");
		return Rat;
	}
}
EstadosEnemy ClientProtocol::decodeEstadoEnemy(uint8_t byte) {

	switch (byte)
	{
	case ENEMY_STATE_IDLE: return EstadosEnemy::Idle;
	case ENEMY_STATE_MOVE: return EstadosEnemy::Move;
	case ENEMY_STATE_ATTACK: return EstadosEnemy::Attack;
	case ENEMY_STATE_DAMAGED: return EstadosEnemy::Damaged;
	case ENEMY_STATE_DEATH: return EstadosEnemy::Death;
	default:
		std::runtime_error("Estado de enemigo no existe. Probablemente se recibio un byte que corresponde a ora cosa");
		return EstadosEnemy::Idle;
	}
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
	EstadosPlayer estado = decodeEstadoPlayer(bytes[5]);
	int vida = decodeInt(bytes[6]);
	int pts = decodeInt(bytes[7]);
	TipoArma arma = TipoArma::Comun;//decodeInt(bytes[contador+8)
	int municion = decodeInt(bytes[9]);
	return InfoPlayer(id, pos_x, pos_y, estado, vida, pts, arma, municion);
}

// modularizarlo despues
InfoJuego ClientProtocol::decodificarMensajeDelServer(const std::vector<uint8_t> &bytes) {
	int cantPlayers = decodeInt(bytes[0]);
	std::cout << "Cantidad de Players: " << cantPlayers << std::endl;
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
	if (cantPlayers == 0)
		contador++;

	int cantEnemigos = decodeInt(bytes[contador]);

	//Decode info Enemigos
	for (int i = 0; i < cantEnemigos; i++) { 
		if (contador + LENGTH_ENEMY_INFO > bytes.size()) {
			std::runtime_error("Error. Faltaron datos de un enemigo. En ClientProtocol::decodificarMensajeDelServer()");
		}
		TipoEnemy tipo = decodeTipoEnemy(bytes[contador+1]);
		int pos_x = decodeInt(bytes[contador+2], bytes[contador+3]) * MULTIPLICADOR_POSICION;
		int pos_y = decodeInt(bytes[contador+4], bytes[contador+5]) * MULTIPLICADOR_POSICION;
		EstadosEnemy estado = decodeEstadoEnemy(bytes[contador+6]);

		infoEnemies.emplace_back(tipo, pos_x, pos_y, estado);
		contador += LENGTH_ENEMY_INFO;
	}
	if (cantEnemigos == 0)
		contador++;
	
	int cantItems = decodeInt(bytes[contador]);
	//Decode info Recolectables
	for (int i = 0; i < cantItems; i++) { 
		if (contador + LENGTH_ITEMS_INFO > bytes.size())
			std::runtime_error("Error. Faltaron datos de un item recolectable. En ClientProtocol::decodificarMensajeDelServer()");
		
		TipoRecolectable tipo = TipoRecolectable::Moneda; 
		int pos_x = decodeInt(bytes[contador+2], bytes[contador+3]) * MULTIPLICADOR_POSICION;
		int pos_y = decodeInt(bytes[contador+4], bytes[contador+5]) * MULTIPLICADOR_POSICION;

		infoItems.emplace_back(tipo, pos_x, pos_y);
		contador += LENGTH_ITEMS_INFO;
	}
	if (cantItems == 0)
		contador++;
	
	int cantProyectiles = decodeInt(bytes[contador]);

	//Decode info proyectiles
	for (int i = 0; i < cantProyectiles; i++) { 
		if (contador + LENGTH_PROYECTIL_INFO > bytes.size())
			std::runtime_error("Error. Faltó info de un proyectil. En ClientProtocol::decodificarMensajeDelServer()");
		
		int pos_x = decodeInt(bytes[contador+1], bytes[contador+2]) * MULTIPLICADOR_POSICION;
		int pos_y = decodeInt(bytes[contador+3], bytes[contador+4]) * MULTIPLICADOR_POSICION;
		
		Direcciones dir = decodeDireccion(bytes[contador+5]);

		infoProyectiles.emplace_back(pos_x, pos_y, dir);
		contador += LENGTH_PROYECTIL_INFO;
	}
	
	return InfoJuego(infoPlayers, infoEnemies, infoItems, infoProyectiles);
}


//metodos publicos

void ClientProtocol::enviarComando(ComandoCliente comando, bool*was_closed_) {
	std::vector<uint8_t> mensaje;
	if (comando.getTipoComando() == MensajeInicial) {
		std::cout << "me uno a la partida" << std::endl;
		mensaje.push_back((uint8_t)comando.getIdPartida());
		mensaje.push_back(codeTipoPlayer(comando.getTipoPlayer()));
	}
	else { //Accion de un player
		mensaje.push_back(id); // necesito saber mi ID de cliente
		mensaje.push_back(codeAccion(comando.getAccion()));
		mensaje.push_back(codeDireccion(comando.getDireccion()));
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
	std::cout << "size " << size<< std::endl;//no se está activando esto
	
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

