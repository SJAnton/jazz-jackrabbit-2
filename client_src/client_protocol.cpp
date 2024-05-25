#include "client_protocol.h"


ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname) :
socket(hostname.c_str(), servname.c_str()) {

}

//ClientProtocol::ClientProtocol(Socket& socket) : socket(socket){}

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