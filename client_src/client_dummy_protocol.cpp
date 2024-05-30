#include <arpa/inet.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "client_dummy_protocol.h"

#define RECV_MSG_SIZE 5

#define SUCCESS 0
#define SHUTCODE 2

ClientProtocol::ClientProtocol(
        const std::string hostname, const std::string servicename) :
        socket(hostname.c_str(), servicename.c_str()) {}

    uint8_t ClientProtocol::get_id(bool &was_closed) {
        uint8_t id;
        socket.recvall(&id, sizeof(id), &was_closed);
        return id;
    }

    int ClientProtocol::send_msg(std::vector<uint8_t> data, bool &was_closed) {
        for (size_t i = 0; i < data.size(); i++) {
            socket.sendall(&data[i], sizeof(data[i]), &was_closed);
        }
        return SUCCESS;
    }

    std::vector<uint8_t> ClientProtocol::recv_msg(bool &was_closed) {
        std::vector<uint8_t> data;
        uint8_t byte;
        for (int i = 0; i < RECV_MSG_SIZE; i++) {
            socket.recvall(&byte, sizeof(byte), &was_closed);
            data.push_back(htons(byte));
        }
        return data;
    }

    int ClientProtocol::disconnect() {
        socket.shutdown(SHUTCODE);
        socket.close();
        return SUCCESS;
    }
