#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <vector>

#include "../common_src/socket.h"

class ClientProtocol {
     private:
          std::string hostname;
          std::string servicename;

          Socket socket;

     public:
          ClientProtocol(std::string hostname, std::string servicename);

          uint8_t get_msg_size(bool &was_closed);

          int send_msg(std::vector<uint8_t> data, bool &was_closed);

          std::vector<uint8_t> recv_msg(int size, bool &was_closed);

          int disconnect();
};
#endif  // CLIENT_PROTOCOL_H_
