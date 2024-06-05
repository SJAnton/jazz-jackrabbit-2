#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "client_dummy_protocol.h"

#define SUCCESS 0
#define SHUTCODE 2

ClientProtocol::ClientProtocol(
        const std::string hostname, const std::string servicename) :
        socket(hostname.c_str(), servicename.c_str()) {}

    uint8_t ClientProtocol::get_msg_size(bool &was_closed) {
        uint8_t size;
        socket.recvall(&size, sizeof(size), &was_closed);
        return size;
    }

    int ClientProtocol::send_msg(std::vector<uint8_t> data, bool &was_closed) {
        int size = data.size();
        for (int i = 0; i < size; i++) {
            socket.sendall(&data[i], sizeof(data[i]), &was_closed);
        }
        return SUCCESS;
    }

    std::vector<uint8_t> ClientProtocol::recv_msg(int size, bool &was_closed) {
        std::vector<uint8_t> data;
        uint8_t byte;
        for (int i = 0; i < size; i++) {
            socket.recvall(&byte, sizeof(byte), &was_closed);
            data.push_back(byte);
        }
        return data;
    }

    int ClientProtocol::disconnect() {
        socket.shutdown(SHUTCODE);
        socket.close();
        return SUCCESS;
    }
