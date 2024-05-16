#include <iostream>
#include "client.h"

Client::Client(Queue<uint8_t>& queueReceptora, Queue<uint8_t>& queueEnviadora) : 
queueReceptora(queueReceptora), queueEnviadora(queueEnviadora){}

void Client::moverDerecha(){
	//QueueEnviadora.push()
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
	//QueueReceptora.pop()
}