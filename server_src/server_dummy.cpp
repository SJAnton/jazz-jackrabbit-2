#include "../common_src/socket.h"
#include <arpa/inet.h>
#include <vector>
#include <iostream>
#include <iomanip> // Para std::hex
#include "server_protocol.h"
#include "../common_src/info_juego.h"

#include "../common_src/constantes_protocolo.h"
#include <chrono>
#include <thread>

#define SERVICENAME argv[1]
int velocidad_x = 4;

void caminar(Direcciones direccion, InfoPlayer &infoPlayer) {
	infoPlayer.estado = EstadosPlayer::Caminando;
	if (direccion == Left) {
		std::cout << "caminar a la izquierda" << std::endl;
		infoPlayer.pos.x -= velocidad_x;
	}
	else {
		std::cout << "caminar a la derecha" << std::endl;
		infoPlayer.pos.x += velocidad_x;
	}
}
void correr(Direcciones direccion, InfoPlayer &infoPlayer) {
	infoPlayer.estado = EstadosPlayer::Corriendo;
	if (direccion == Left) {
		std::cout << "correr a la izquierda" << std::endl;
	}
	else {
		std::cout << "correr a la derecha" << std::endl;
	}
}
void saltar(Direcciones direccion, InfoPlayer &infoPlayer) {
	infoPlayer.estado = EstadosPlayer::Saltando;
	if (direccion == Left) {
		std::cout << "saltar a la izquierda" << std::endl;
	}
	else {
		std::cout << "saltar a la derecha" << std::endl;
	}
}
void disparar(Direcciones direccion, InfoPlayer &infoPlayer) {
	infoPlayer.estado = EstadosPlayer::Disparando;
	if (direccion == Left) {
		std::cout << "disparar a la izquierda" << std::endl;
	}
	else {
		std::cout << "disparar a la derecha" << std::endl;
	}
}
void ataqueEspecial(Direcciones direccion, InfoPlayer &infoPlayer) {
	infoPlayer.estado = EstadosPlayer::AtaqueEspecial;
	if (direccion == Left) {
		std::cout << "ataque especial a la izquierda" << std::endl;
	}
	else {
		std::cout << "ataque especial a la derecha" << std::endl;
	}
}

int main(int argc, char const *argv[])
{
	
	Socket skt(SERVICENAME);
	Socket clientSocket = skt.accept();
	ServerProtocol protocolo;

	InfoPlayer infoPlayer;
	//inicializo por defecto
	infoPlayer.pos = Position(0, 256);
	infoPlayer.estado = Inactivo;
	infoPlayer.puntos = 0;
	infoPlayer.vida = 10;

	bool cerrado = false;
	std::vector<uint8_t> buffer(3);
	while(not cerrado) {
		clientSocket.recvall(buffer.data(), 3, &cerrado);
		/*
		std::cout << "Mensaje recibido: ";
		for (uint8_t byte : buffer) {
			std::cout << std::hex << std::setw(2) << static_cast<int>(byte) << " ";
		}
		std::cout << std::endl;
		*/
		uint8_t idPlayer = buffer[0];
		AccionesPlayer accion = protocolo.decodeAction(buffer[1]);
		Direcciones direccion = protocolo.decodeDireccion(buffer[2]);

		switch (accion)
		{
		case Idle:
			std::cout << "inactivo" << std::endl;
			break;
		case Walk: caminar(direccion,infoPlayer);
			break;
		case Run: correr(direccion, infoPlayer);
			break;
		case Jump: saltar(direccion, infoPlayer);
			break;
		case Shoot: disparar(direccion, infoPlayer);
			break;
		case SpecialAttack: ataqueEspecial(direccion, infoPlayer);
			break;
		default:
			//Excepcion
			break;
		}
		InfoJuego info(infoPlayer);

		//protocolo.enviarAlCliente(infoJuego);

		//Esto se haria en un metodo protocolo.codificarMensaje()
		int x = info.player1.pos.x;
		int y = info.player1.pos.y;
		uint8_t x1 = (x >> 8) & 0xFF; // Obtener el byte más significativo
    	uint8_t x2 = x & 0xFF; // Obtener el byte menos significativo
		uint8_t y1 = (y >> 8) & 0xFF; // Obtener el byte más significativo
    	uint8_t y2 = y & 0xFF; // Obtener el byte menos significativo
		uint8_t state = protocolo.codeEstado(info.player1.estado);
		std::vector<uint8_t> bytes = {0x00, 0x08, PLAYER_1, x1, x2, y1, y2, state, 0x0A, 0x00};
		
		clientSocket.sendall(bytes.data(),bytes.size(),&cerrado);
		//std::this_thread::sleep_for(std::chrono::milliseconds(67));

	}
	return 0;
}

/**
 * Server falso para enviarle cosas al cliente
 * Se puede usar para probar el protocolo y 
 * para implementar las funcionalidades de client
 * sin tener que usar el server posta
 *
*/