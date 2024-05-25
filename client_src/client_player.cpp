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
	sender.start();
	receiver.start();
}


void ClientPlayer::caminar(Direcciones direccion){
	ComandoCliente comando(AccionesPlayer::Walk, direccion);
	queueEnviadora.push(comando);

	if (direccion == Right)
		std::cout << "Moverse a la derecha" << std::endl;
	else
		std::cout << "Moverse a la izquierda" << std::endl;
}


void ClientPlayer::saltar(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::Jump, direccion));
	std::cout << "Saltar" << std::endl;
}

void ClientPlayer::correr(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::Run, direccion));
	std::cout << "Correr" << std::endl;
}

void ClientPlayer::disparar(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::Shoot, direccion));
	std::cout << "Disparar" << std::endl;
}

void ClientPlayer::ataque_especial(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::SpecialAttack, direccion));
	std::cout << "Ataque especial" << std::endl;
}

void ClientPlayer::recibirInformacion(){
	//QueueReceptora.pop()
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
