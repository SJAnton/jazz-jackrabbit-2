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
	nombres_niveles = protocolo.recibirNombresNiveles(&was_closed);

	protocolo.enviarNivelElegido("demo", &was_closed);

	sender.start();
}


void ClientPlayer::caminar(Direcciones direccion){
	ComandoCliente comando(AccionesPlayer::Walk, direccion);
	queueEnviadora.push(comando);
}

void ClientPlayer::saltar(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::Jump, direccion));
}

void ClientPlayer::correr(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::Run, direccion));
}

void ClientPlayer::disparar(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::Shoot, direccion));
}

void ClientPlayer::ataque_especial(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::SpecialAttack, direccion));
}

void ClientPlayer::cambiar_arma(Direcciones direccion) {
	queueEnviadora.push(ComandoCliente(AccionesPlayer::ChangeWeapon, direccion));
}

TileMap ClientPlayer::recibirInformacion(){
	protocolo.recibirIDCliente();
	TileMap tilemap = protocolo.recibirMapa();
	return tilemap;
}

void ClientPlayer::startReceiver() {
	receiver.start();
}

std::vector<int> ClientPlayer::getIdPartidas() {
	return ids_partidas;
}

std::vector<std::string> ClientPlayer::getNombresNiveles() {
	return nombres_niveles;
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
