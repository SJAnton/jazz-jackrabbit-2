#include "client_protocol.h"

#include <vector>
#include <exception>
#include <iostream>
#include <iomanip>

#define MULTIPLICADOR_POSICION 4


ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname) :
socket(hostname.c_str(), servname.c_str()) {

}
//metodos privados
uint8_t ClientProtocol::codeAccion(AccionesPlayer accion) {
	switch (accion) {
		case AccionesPlayer::Idle: return ACTION_IDLE;
		case AccionesPlayer::Walk: return ACTION_WALK;
		case AccionesPlayer::Run: return ACTION_RUN;
		case AccionesPlayer::Jump: return ACTION_JUMP;
		case AccionesPlayer::Shoot: return ACTION_SHOOT;
		case AccionesPlayer::SpecialAttack: return ACTION_SPECIAL_ATACK;
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

Direcciones ClientProtocol::decodeDireccion(uint8_t dir) {
	switch (dir) {
		case LEFT: return Left;
		case RIGHT: return Right;
		default: 
		throw std::runtime_error("ERROR. Direccion invalida");
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



// CHEQUEAR ESTAS FUNCIONES!
int ClientProtocol::decodeInt(uint8_t byte) {
    return static_cast<int>(byte);
}
int ClientProtocol::decodeInt(uint8_t byte1, uint8_t byte2) {
    // Combine los bytes en un uint16_t
    uint16_t combined = (static_cast<uint16_t>(byte1) << 8) | static_cast<uint16_t>(byte2);
    // Convertir del orden de bytes del host al orden de bytes de la red (big-endian)
    uint16_t networkOrder = htons(combined);
    // Convertir de nuevo del orden de bytes de la red al orden de bytes del host
    uint16_t hostOrder = ntohs(networkOrder);
    // Convertir el resultado a un entero con signo
    return static_cast<int>(hostOrder);
}


// modularizar
InfoJuego ClientProtocol::decodificarMensajeDelServer(const std::vector<uint8_t> &bytes) {
	int cantPlayers = decodeInt(bytes[0]);

	if (cantPlayers* LENGTH_PLAYER_INFO > bytes.size()){
		std::runtime_error("Error en el mensaje recibido. En ClientProtocol::decodificarMensajeDelServer()");
	}
	int contador = 0;
	
	std::vector<InfoPlayer> infoPlayers;
	std::vector<InfoEnemigo> infoEnemies;
	std::vector<InfoRecolectable> infoItems;
	std::vector<InfoProyectil> infoProyectiles;

	//Decode info Players
	for (int i = 0; i < cantPlayers; i++) { 
		if (contador + LENGTH_PLAYER_INFO > bytes.size()) {
			std::runtime_error("Error. Faltaron datos de un player. En ClientProtocol::decodificarMensajeDelServer()");
		}
		int id = decodeInt(bytes[contador+1]);
		int pos_x = decodeInt(bytes[contador+2], bytes[contador+3]) * MULTIPLICADOR_POSICION;
		int pos_y = decodeInt(bytes[contador+4], bytes[contador+5]) * MULTIPLICADOR_POSICION;
		EstadosPlayer estado = decodeEstadoPlayer(bytes[contador+6]);
		int vida = decodeInt(bytes[contador+7]);
		int pts = decodeInt(bytes[contador+8]);
		TipoArma arma = TipoArma::Comun;//decodeInt(bytes[contador+9)
		int municion = decodeInt(bytes[contador+10]);

		infoPlayers.emplace_back(id,pos_x, pos_y, estado, vida, pts, arma, municion);

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
	for (int i = 0; i < cantItems; i++) { 
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

void ClientProtocol::enviarComandoAlServer(ComandoCliente comando, bool*was_closed) {
	std::vector<uint8_t> mensaje;
	mensaje.push_back(id); // necesito saber mi ID de cliente
	mensaje.push_back(codeAccion(comando.accion));
	mensaje.push_back(codeDireccion(comando.direccion));

	
	int enviados = socket.sendall(mensaje.data(), SIZE_CLIENT_MSG, was_closed);	
	std::cout << "se enviaron " << enviados << " bytes." << std::endl;
}



InfoJuego ClientProtocol::recibirInformacionDelServer(bool *was_closed) {
	uint8_t aux[2];
	int r = socket.recvall(&aux,2, was_closed);	//recibo los primeros 2 bytes que indican el size del mensaje


	int size = (aux[0] << 8) | aux[1];//convertir los 2 bytes al numero entero

    std::vector<uint8_t> bytes(size); //= {0xA1, 0x00, 0x02, 0x00, 0xFF, 0x01, 0x02, 0x0A, 0x00, 0x00};
	r = socket.recvall(bytes.data(), size, was_closed);
	std::cout << "Recibí " << r << " bytes." << std::endl;
	if (*was_closed)
		return InfoJuego();
	std::cout << "Mensaje recibido: ";
		for (uint8_t byte : bytes) {
			std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
		}
		std::cout << std::endl;
	InfoJuego infoJuego = decodificarMensajeDelServer(bytes);
	return infoJuego;
}

void ClientProtocol::close() {
	socket.shutdown(2);
	socket.close();
}

#define SUCCESS 0
#define SHUTCODE 2


 uint8_t ClientProtocol::get_msg_size(bool &was_closed) {
        uint8_t size;
        socket.recvall(&size, sizeof(size), &was_closed);
        return size;
    }

    int ClientProtocol::send_msg(std::vector<uint8_t> data, bool &was_closed) {
        int size = data.size();
        for (int i = 0; i < size; i++) {
            socket.sendall(&data[i], sizeof(data[i]), &was_closed);
        }
        return SUCCESS;
    }

 std::vector<uint8_t> ClientProtocol::recv_msg(int size, bool &was_closed) {
        std::vector<uint8_t> data;
        uint8_t byte;
        for (int i = 0; i < size; i++) {
            socket.recvall(&byte, sizeof(byte), &was_closed);
            data.push_back(byte);
        }
        return data;
    }

