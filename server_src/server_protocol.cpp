#include "server_protocol.h"

#include <iostream>

#define SUCCESS 0
#define SHUTCODE 2

#define INIT_MSG_SIZE 2
#define MSG_SIZE 3

std::vector<uint8_t> ServerProtocol::recv_init_msg(bool &was_closed) {
    std::vector<uint8_t> data;
    uint8_t byte;
    for (int i = 0; i < INIT_MSG_SIZE; i++) {
        sk.recvall(&byte, sizeof(byte), &was_closed);
        data.push_back(byte);
    }
    return data;
}

void ServerProtocol::send_id(uint8_t id, bool &was_closed) {
    sk.sendall(&id, sizeof(id), &was_closed);
}

std::vector<uint8_t> ServerProtocol::recv_msg(bool &was_closed) {
    std::vector<uint8_t> data;
    uint8_t byte;
    for (int i = 0; i < MSG_SIZE; i++) {
        sk.recvall(&byte, sizeof(byte), &was_closed);
        data.push_back(byte);
    }
    return data;
}

void ServerProtocol::send_msg(std::vector<uint8_t> &msg, bool &was_closed) {
    int size = msg.size();
    for (int i = 0; i < size; i++) {
        uint8_t byte = msg[i];
        sk.sendall(&byte, sizeof(byte), &was_closed);
    }
}

void ServerProtocol::send_game_data(InfoJuego &game_data, bool &was_closed) {
    
}

int ServerProtocol::disconnect() {
    sk.shutdown(SHUTCODE);
    sk.close();
    return SUCCESS;
}
