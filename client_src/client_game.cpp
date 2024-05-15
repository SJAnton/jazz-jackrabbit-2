#include <iostream>
#include "client.h"

Client::Client(){}

void Client::moverDerecha(){
	//Envio mensaje al protocolo para que se lo envie al server
	std::cout << "Moverse a la derecha" << std::endl;
}

void Client::moverIzquierda(){
	std::cout << "Moverse a la izquierda" << std::endl;
}

void Client::saltar(){
	std::cout << "Saltar" << std::endl;
}

void Client::correr(){
	std::cout << "Correr" << std::endl;
}

void Client::disparar(){
	std::cout << "Disparar" << std::endl;
}

void Client::ataque_especial(){
	std::cout << "Ataque especial" << std::endl;
}

void Client::recibirInformacion(){
	//Pido al protocolo que reciba mensajes
	//Retorno a la interfaz la informacion
}