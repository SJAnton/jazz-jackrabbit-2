#include "../common_src/socket.h"
#include <arpa/inet.h>

#define SERVICENAME argv[1]

int main(int argc, char const *argv[])
{
	
	Socket skt(SERVICENAME);
	Socket clientSocket = skt.accept();

	bool cerrado = false;
	while(not cerrado){
		uint8_t accion;
		clientSocket.recvall(&accion, 1, &cerrado); //Enviá lo que quieras por acá
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