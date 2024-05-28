#include "client_protocol.h"

#include <vector>
#include <exception>
#include <iostream>
#include <iomanip>

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname) :
socket(hostname.c_str(), servname.c_str()) {

}
//metodos privados
uint8_t ClientProtocol::codeAccion(AccionesPlayer accion) {
	switch (accion) {
		case Idle: return ACTION_IDLE;
		case Walk: return ACTION_WALK;
		case Run: return ACTION_RUN;
		case Jump: return ACTION_JUMP;
		case Shoot: return ACTION_SHOOT;
		case SpecialAttack: return ACTION_SPECIAL_ATACK;
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
EstadosPlayer ClientProtocol::decodeEstadoPlayer(uint8_t byte) {
    switch (byte) {
        case STATE_IDLE: return EstadosPlayer::Inactivo;
        case STATE_WALK: return EstadosPlayer::Caminando;
        case STATE_RUN: return EstadosPlayer::Corriendo;
        case STATE_JUMP: return EstadosPlayer::Saltando;
        case STATE_FALL: return EstadosPlayer::Cayendo;
        case STATE_SHOOT: return EstadosPlayer::Disparando;
        case STATE_SPECIAL_ATTACK: return EstadosPlayer::AtaqueEspecial;
        case STATE_INTOXICATED_IDLE: return EstadosPlayer::IntoxicadoIdle;
		case STATE_INTOXICATED_WALK: return EstadosPlayer::IntoxicadoWalk;
        case STATE_DAMAGED: return EstadosPlayer::Impactado;
        case STATE_DYING: return EstadosPlayer::Muriendo;
        case STATE_DEAD: return EstadosPlayer::Muerto;
        case STATE_REVIVE: return EstadosPlayer::Reviviendo;
        default: 
		throw std::runtime_error("ERROR. EstadoPlayer invalido. Probablemente estas pasando un byte que corresponde a otra cosa");
		return EstadosPlayer::Inactivo;
    }
}



InfoJuego ClientProtocol::decodificarMensajeDelServer(const std::vector<uint8_t> &bytes) {
	uint8_t id = bytes[0];
    uint16_t x = (bytes[1] << 8) | bytes[2];
    uint16_t y = (bytes[3] << 8) | bytes[4];
    EstadosPlayer estadoActual = decodeEstadoPlayer(bytes[5]);
    uint8_t vida = bytes[6];
    uint8_t puntos = bytes[7];

    Position pos(x, y);


	InfoPlayer infoPlayer;
	infoPlayer.estado = estadoActual;
	infoPlayer.pos = pos;
	infoPlayer.vida = (int)vida;
	infoPlayer.puntos = (int)puntos;
	return InfoJuego(std::move(infoPlayer));
}

//metodos publicos

void ClientProtocol::enviarComandoAlServer(ComandoCliente comando, bool*was_closed) {
	std::vector<uint8_t> mensaje;
	mensaje.push_back(PLAYER_1); // necesito saber mi ID de cliente
	mensaje.push_back(codeAccion(comando.accion));
	mensaje.push_back(codeDireccion(comando.direccion));

	
	int enviados = socket.sendall(mensaje.data(), SIZE_CLIENT_MSG, was_closed);	
	std::cout << "se enviaron " << enviados << " bytes." << std::endl;
}



InfoJuego ClientProtocol::recibirInformacionDelServer(bool *was_closed) {

	uint8_t aux[2];
	//recibo los primeros 2 bytes que indican el size del mensaje
	int r = socket.recvall(&aux,2, was_closed);

	int size = (aux[0] << 8) | aux[1];//convertir los 2 bytes al numero entero

    std::vector<uint8_t> bytes(size); //= {0xA1, 0x00, 0x02, 0x00, 0xFF, 0x01, 0x02, 0x0A, 0x00, 0x00};
	r = socket.recvall(bytes.data(), size, was_closed);
	/*std::cout << "Recibí " << r << " bytes." << std::endl;
	std::cout << "Mensaje recibido: ";
		for (uint8_t byte : bytes) {
			std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
		}
		std::cout << std::endl;
	*/
	InfoJuego infoJuego = decodificarMensajeDelServer(bytes);
	return infoJuego;
}
