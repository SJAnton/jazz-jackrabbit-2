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
	std::cout << "posy " << infoPlayer.pos_y << std::endl;
	infoPlayer.estado = EstadosPlayer::Walking;
	if (direccion == Left) {
		std::cout << "caminar a la izquierda" << std::endl;
		infoPlayer.pos_x -= velocidad_x;
	}
	else {
		std::cout << "caminar a la derecha" << std::endl;
		infoPlayer.pos_x += velocidad_x;
	}
}
void correr(Direcciones direccion, InfoPlayer &infoPlayer) {
	infoPlayer.estado = EstadosPlayer::Running;
	if (direccion == Left) {
		std::cout << "correr a la izquierda" << std::endl;
	}
	else {
		std::cout << "correr a la derecha" << std::endl;
	}
}
void saltar(Direcciones direccion, InfoPlayer &infoPlayer) {
	infoPlayer.estado = EstadosPlayer::Jumping;
	if (direccion == Left) {
		std::cout << "saltar a la izquierda" << std::endl;
	}
	else {
		std::cout << "saltar a la derecha" << std::endl;
	}
}
void disparar(Direcciones direccion, InfoPlayer &infoPlayer) {
	infoPlayer.estado = EstadosPlayer::Shooting;
	if (direccion == Left) {
		std::cout << "disparar a la izquierda" << std::endl;
	}
	else {
		std::cout << "disparar a la derecha" << std::endl;
	}
}
void ataqueEspecial(Direcciones direccion, InfoPlayer &infoPlayer) {
	infoPlayer.estado = EstadosPlayer::SpecialAttack;
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
	
	std::vector<InfoPlayer> infoPlayers;
	std::vector<InfoEnemigo> infoEnemigos;
	std::vector<InfoRecolectable> infoItems;
	std::vector<InfoProyectil> infoProyectiles;

	InfoPlayer infoPlayer ;
	//inicializo por defecto
	infoPlayers.emplace_back(1, 0, 64, EstadosPlayer::Inactive, 10, 0, TipoArma::Comun, 255);
	std::cout << "posy " << infoPlayers[0].pos_y << std::endl;
	
	
	bool cerrado = false;
	std::vector<uint8_t> buffer(3);

	while(not cerrado) {
		clientSocket.recvall(buffer.data(), 3, &cerrado);
		std::cout << "comando recibido"<<std::endl;
		uint8_t idPlayer = buffer[0];
		AccionesPlayer accion = protocolo.decodeAction(buffer[1]);
		Direcciones direccion = protocolo.decodeDireccion(buffer[2]);

		switch (accion)
		{
		case AccionesPlayer::Idle:
			std::cout << "inactivo" << std::endl;
			break;
		case AccionesPlayer::Walk: caminar(direccion,infoPlayers[0]);
			break;
		case AccionesPlayer::Run: correr(direccion, infoPlayers[0]);
			break;
		case AccionesPlayer::Jump: saltar(direccion, infoPlayers[0]);
			break;
		case AccionesPlayer::Shoot: disparar(direccion, infoPlayers[0]);
			break;
		case AccionesPlayer::SpecialAttack: ataqueEspecial(direccion, infoPlayers[0]);
			break;
		default:
			//Excepcion
			break;
		}
		
		InfoJuego info(infoPlayers, infoEnemigos, infoItems, infoProyectiles);

		//protocolo.enviarAlCliente(infoJuego);
		auto bytes = protocolo.encodeInfoJuego(info);
		
		clientSocket.sendall(bytes.data(),bytes.size(),&cerrado);

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