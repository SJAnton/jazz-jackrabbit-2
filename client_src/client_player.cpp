#include <iostream>
#include "client_player.h"

ClientPlayer::ClientPlayer(){}

void ClientPlayer::moverDerecha(){
	//Envio mensaje al protocolo para que se lo envie al server
	std::cout << "Moverse a la derecha" << std::endl;
}

void ClientPlayer::moverIzquierda(){
	std::cout << "Moverse a la izquierda" << std::endl;
}

void ClientPlayer::saltar(){
	std::cout << "Saltar" << std::endl;
}

void ClientPlayer::correr(){
	std::cout << "Correr" << std::endl;
}

void ClientPlayer::disparar(){
	std::cout << "Disparar" << std::endl;
}

void ClientPlayer::ataque_especial(){
	std::cout << "Ataque especial" << std::endl;
}

void ClientPlayer::recibirInformacion(){
	//Pido al protocolo que reciba mensajes
	//Retorno a la interfaz la informacion
}