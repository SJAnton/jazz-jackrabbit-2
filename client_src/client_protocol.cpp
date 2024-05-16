#include "client_protocol.h"
#include "socket.h"

ClientProtocol::ClientProtocol(Socket& socket) : socket(socket){}

uint8_t ClientProtocol::recv_action(bool &was_closed) {
	uint8_t accion = 0;
	//recibir del server
	return accion;
}

int ClientProtocol::send_action(uint8_t &action, bool &was_closed) {
	uint8_t accion = 0;
	//mandar accion
	return 0;
}