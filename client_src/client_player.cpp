#include <iostream>
#include "client_player.h"

// Definición e inicialización de las colas estáticas
Queue<InfoJuego> ClientPlayer::queueReceptora;
Queue<ComandoCliente> ClientPlayer::queueEnviadora;

ClientPlayer::ClientPlayer(const std::string& hostname, const std::string& servname) :
	protocolo(hostname, servname),
	receiver(protocolo, queueReceptora),
	sender(protocolo, queueEnviadora)
{
	bool was_closed;
	ids_partidas = protocolo.recibirIdsPartidas(&was_closed);
	//ids_partidas.push_back(0);//temporal
	//ids_partidas.push_back(2);
	
	sender.start();
}


void ClientPlayer::caminar(Direcciones direccion){
	ComandoCliente comando(AccionesPlayer::Walk, direccion);
	queueEnviadora.push(comando);

	//if (direccion == Right)
		//std::cout << "Moverse a la derecha" << std::endl;
	//else
		//std::cout << "Moverse a la izquierda" << std::endl;
}


void ClientPlayer::saltar(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::Jump, direccion));
	//std::cout << "Saltar" << std::endl;
}

void ClientPlayer::correr(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::Run, direccion));
	//std::cout << "Correr" << std::endl;
}

void ClientPlayer::disparar(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::Shoot, direccion));
	//std::cout << "Disparar" << std::endl;
}

void ClientPlayer::ataque_especial(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::SpecialAttack, direccion));
	//std::cout << "Ataque especial" << std::endl;
}

void ClientPlayer::cambiar_arma(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::ChangeWeapon, direccion));
	//std::cout << "Cambiar arma" << std::endl;
}

void ClientPlayer::recibirInformacion(){
	protocolo.recibirIDCliente();
	//protocolo.recibirTerreno();
	receiver.start();
}
std::vector<int> ClientPlayer::getIdPartidas() {
	return ids_partidas;
}


void ClientPlayer::entrarPartida(int idPartida, const TipoPlayer &tipoPlayer) {
	queueEnviadora.push(ComandoCliente(idPartida, tipoPlayer));
}

ClientPlayer::~ClientPlayer() {
    // Señalar a los hilos que terminen
    sender.stop();
    receiver.stop();

    // Esperar a que los hilos realmente terminen
    sender.join();
    receiver.join();

    // Limpieza adicional si es necesaria
}
