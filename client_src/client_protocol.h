#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "../common_src/socket.h"
#include <string>
#include <arpa/inet.h>

class ClientProtocol{
	private:
		Socket socket;
	public:
		ClientProtocol(const std::string& hostname, const std::string& servname);
		//ClientProtocol(Socket& socket);
		uint8_t recv_action(bool&);
		int send_action(uint8_t&, bool&);
};

#endif
