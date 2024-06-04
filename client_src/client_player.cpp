#include <iostream>
#include "client_player.h"
#include "client_dummy_app.h"

//#include "client_dummy_protocol.h"


#define MOV_IZQ "IZQ"
#define MOV_DER "DER"
#define EXIT "q"

#define ID_MSG_SIZE 1

#define EXIT_BYTE 0xFF

#define SUCCESS 0
#define ERROR 1
// Definición e inicialización de las colas estáticas
Queue<InfoJuego> ClientPlayer::queueReceptora;
Queue<ComandoCliente> ClientPlayer::queueEnviadora;

ClientPlayer::ClientPlayer(const std::string& hostname, const std::string& servname) :
	protocolo(hostname, servname),
	receiver(protocolo, queueReceptora),
	sender(protocolo, queueEnviadora) 
{
	// Elección de partida y personaje
	ClientApp app(protocolo);
	bool was_closed = false;
    app.get_games(was_closed);
    std::vector<uint8_t> init_data = app.choose_game_and_character();
    protocolo.send_msg(init_data, was_closed);

    // ID del cliente
    uint8_t client_id = protocolo.recv_msg(ID_MSG_SIZE, was_closed)[0];
    std::cout << "ID del cliente: " << static_cast<int>(client_id) << std::endl;
	protocolo.id = client_id;



	
	sender.start();
	std::cout << "sender corriendo";
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
